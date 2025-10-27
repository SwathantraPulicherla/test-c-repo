```c
#include "unity.h"
#include "temp_sensor.h"

// Include the header file for the function stubs
#include "temp_converter.h"

// Stubs
int raw_to_celsius_CallCount = 0;
float raw_to_celsius_ReturnVal;

float raw_to_celsius(int raw) {
    raw_to_celsius_CallCount++;
    return raw_to_celsius_ReturnVal;
}


void setUp(void) {
    raw_to_celsius_CallCount = 0;
    raw_to_celsius_ReturnVal = 0.0f;
}

void tearDown(void) {
    // clean stuff up here
}

void test_read_temperature_raw_returns_value_between_0_and_1023(void) {
    for (int i = 0; i < 100; i++) {
        int raw_temp = read_temperature_raw();
        TEST_ASSERT_GREATER_OR_EQUAL_INT(0, raw_temp);
        TEST_ASSERT_LESS_OR_EQUAL_INT(1023, raw_temp);
    }
}

void test_validate_temperature_range_within_range_returns_true(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f));
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_outside_range_returns_false(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-41.0f));
    TEST_ASSERT_FALSE(validate_temperature_range(126.0f));
}

void test_check_temperature_status_critical(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(121.0f));
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(150.0f));
}

void test_check_temperature_status_hot(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(86.0f));
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void test_check_temperature_status_cold(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-11.0f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-50.0f));
}

void test_check_temperature_status_normal(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(20.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-10.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_get_temperature_celsius_calls_raw_to_celsius(void) {
    raw_to_celsius_ReturnVal = 25.0f;
    float temp = get_temperature_celsius();
    TEST_ASSERT_EQUAL_INT(1, raw_to_celsius_CallCount);
}

void test_get_temperature_celsius_returns_converted_temperature(void) {
    raw_to_celsius_ReturnVal = 25.0f;
    float temp = get_temperature_celsius();
    TEST_ASSERT_EQUAL_FLOAT(25.0f, temp);

    raw_to_celsius_ReturnVal = -10.5f;
    temp = get_temperature_celsius();
    TEST_ASSERT_EQUAL_FLOAT(-10.5f, temp);

    raw_to_celsius_ReturnVal = 100.0f;
    temp = get_temperature_celsius();
    TEST_ASSERT_EQUAL_FLOAT(100.0f, temp);

}
```