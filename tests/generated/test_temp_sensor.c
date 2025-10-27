#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"

static int raw_to_celsius_Called;
static float raw_to_celsius_Return;

void setUp(void) {
    raw_to_celsius_Called = 0;
    raw_to_celsius_Return = 0.0f;
}

void tearDown(void) {
    raw_to_celsius_Called = 0;
    raw_to_celsius_Return = 0.0f;
}

float raw_to_celsius(int raw) {
    raw_to_celsius_Called++;
    return raw_to_celsius_Return;
}

void test_read_temperature_raw_returns_within_range(void) {
    for (int i = 0; i < 10; i++) {
        int raw_temp = read_temperature_raw();
        TEST_ASSERT_TRUE(raw_temp >= 0 && raw_temp <= 1023);
    }
}

void test_validate_temperature_range_normal_temp(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void test_validate_temperature_range_min_temp(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f));
}

void test_validate_temperature_range_max_temp(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_below_min(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-41.0f));
}

void test_validate_temperature_range_above_max(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(126.0f));
}

void test_check_temperature_status_critical(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(121.0f));
}

void test_check_temperature_status_hot(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(86.0f));
}

void test_check_temperature_status_cold(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-11.0f));
}

void test_check_temperature_status_normal(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(20.0f));
}

void test_get_temperature_celsius(void) {
    raw_to_celsius_Return = 25.5f;
    float temp = get_temperature_celsius();
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 25.5f, temp);
    TEST_ASSERT_EQUAL(1, raw_to_celsius_Called);
}

void test_get_temperature_celsius_edge_case(void) {
    raw_to_celsius_Return = -40.0f;
    float temp = get_temperature_celsius();
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, temp);
    TEST_ASSERT_EQUAL(1, raw_to_celsius_Called);
}
