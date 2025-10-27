#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"

// Stubs
static int get_temperature_celsius_call_count;
static float get_temperature_celsius_return_value;
static int check_temperature_status_call_count;
static const char* check_temperature_status_return_value;

float get_temperature_celsius(void) {
  get_temperature_celsius_call_count++;
  return get_temperature_celsius_return_value;
}

const char* check_temperature_status(float temp_c) {
  check_temperature_status_call_count++;
  return check_temperature_status_return_value;
}

void setUp(void) {
    get_temperature_celsius_call_count = 0;
    get_temperature_celsius_return_value = 0.0f;
    check_temperature_status_call_count = 0;
    check_temperature_status_return_value = "NORMAL";
}

void tearDown(void) {
    // Reset stubs
    get_temperature_celsius_call_count = 0;
    check_temperature_status_call_count = 0;
}

void test_main_normal_temperature_flow(void) {
    // Setup: Normal temperature scenario
    get_temperature_celsius_return_value = 25.0f;
    check_temperature_status_return_value = "NORMAL";

    // Exercise: Call the functions as main() does
    float temp = get_temperature_celsius();
    const char* status = check_temperature_status(temp);

    // Verify: Check both function calls and return values
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 25.0f, temp);
    TEST_ASSERT_EQUAL_STRING("NORMAL", status);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_call_count);
    TEST_ASSERT_EQUAL(1, check_temperature_status_call_count);
}

void test_main_critical_temperature_flow(void) {
    // Setup: Critical temperature scenario
    get_temperature_celsius_return_value = 100.0f;
    check_temperature_status_return_value = "CRITICAL";

    // Exercise
    float temp = get_temperature_celsius();
    const char* status = check_temperature_status(temp);

    // Verify
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 100.0f, temp);
    TEST_ASSERT_EQUAL_STRING("CRITICAL", status);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_call_count);
    TEST_ASSERT_EQUAL(1, check_temperature_status_call_count);
}

void test_main_cold_temperature_flow(void) {
    // Setup: Cold temperature scenario
    get_temperature_celsius_return_value = -15.0f;
    check_temperature_status_return_value = "COLD";

    // Exercise
    float temp = get_temperature_celsius();
    const char* status = check_temperature_status(temp);

    // Verify
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -15.0f, temp);
    TEST_ASSERT_EQUAL_STRING("COLD", status);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_call_count);
    TEST_ASSERT_EQUAL(1, check_temperature_status_call_count);
}

void test_main_hot_temperature_flow(void) {
    // Setup: Hot temperature scenario
    get_temperature_celsius_return_value = 90.0f;
    check_temperature_status_return_value = "HOT";

    // Exercise
    float temp = get_temperature_celsius();
    const char* status = check_temperature_status(temp);

    // Verify
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 90.0f, temp);
    TEST_ASSERT_EQUAL_STRING("HOT", status);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_call_count);
    TEST_ASSERT_EQUAL(1, check_temperature_status_call_count);
}
