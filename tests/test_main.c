
#include "unity.h"
// Include the headers for the functions that main.c uses.
// These headers are assumed to declare the functions used in main.c.
#include "temp_sensor.h"
#include "temp_converter.h"

// Define a small delta for float comparisons to account for floating-point inaccuracies
#define FLOAT_DELTA 0.0001f

// --- Setup and Teardown Functions ---

void setUp(void) {
    // This function is called before each test function.
    // Use it to initialize variables or states common to all tests.
}

void tearDown(void) {
    // This function is called after each test function.
    // Use it to clean up resources.
}

// --- Test Functions for get_temperature_celsius() ---

// IMPORTANT ASSUMPTION FOR get_temperature_celsius():
// The actual implementation of `get_temperature_celsius()` is not provided.
// In a real-world scenario, this function would likely read from hardware, making its
// return value non-deterministic. To enable deterministic unit testing without
// redefinition or mocking (which are forbidden), we must assume that for testing
// purposes, the underlying implementation of `get_temperature_celsius()` provides
// a consistent, fixed value (e.g., 25.0f) when called in a test environment.
// If its actual behavior is to read a live sensor, this unit test will be dependent
// on the current sensor reading, potentially leading to non-deterministic test results.
void test_get_temperature_celsius_returns_assumed_fixed_value(void) {
    float actual_temperature = get_temperature_celsius();
    // Assuming the function returns 25.0f for testing. Adjust this expected value
    // if the actual, non-mocked implementation returns a different constant.
    TEST_MESSAGE("NOTE: This test assumes get_temperature_celsius() returns a fixed value (e.g., 25.0f) for determinism. If it reads a live sensor, this test will be non-deterministic.");
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, 25.0f, actual_temperature);
}


// --- Test Functions for check_temperature_status() ---

// IMPORTANT ASSUMPTION FOR check_temperature_status():
// The behavior of `check_temperature_status()` is not explicitly documented,
// but based on common temperature monitoring logic, we assume the following thresholds:
// - "Low" for temperatures strictly less than 10.0f
// - "Normal" for temperatures greater than or equal to 10.0f AND less than or equal to 30.0f
// - "High" for temperatures strictly greater than 30.0f

void test_check_temperature_status_normal_at_low_boundary(void) {
    float temp = 10.0f;
    TEST_ASSERT_EQUAL_STRING("Normal", check_temperature_status(temp));
}

void test_check_temperature_status_normal_mid_range(void) {
    float temp = 20.5f;
    TEST_ASSERT_EQUAL_STRING("Normal", check_temperature_status(temp));
}

void test_check_temperature_status_normal_at_high_boundary(void) {
    float temp = 30.0f;
    TEST_ASSERT_EQUAL_STRING("Normal", check_temperature_status(temp));
}

void test_check_temperature_status_low_just_below_boundary(void) {
    float temp = 9.9f;
    TEST_ASSERT_EQUAL_STRING("Low", check_temperature_status(temp));
}

void test_check_temperature_status_low_general_value(void) {
    float temp = 5.0f;
    TEST_ASSERT_EQUAL_STRING("Low", check_temperature_status(temp));
}

void test_check_temperature_status_low_edge_negative(void) {
    float temp = -5.0f;
    TEST_ASSERT_EQUAL_STRING("Low", check_temperature_status(temp));
}

void test_check_temperature_status_low_edge_zero(void) {
    float temp = 0.0f;
    TEST_ASSERT_EQUAL_STRING("Low", check_temperature_status(temp));
}

void test_check_temperature_status_high_just_above_boundary(void) {
    float temp = 30.1f;
    TEST_ASSERT_EQUAL_STRING("High", check_temperature_status(temp));
}

void test_check_temperature_status_high_general_value(void) {
    float temp = 35.0f;
    TEST_ASSERT_EQUAL_STRING("High", check_temperature_status(temp));
}

void test_check_temperature_status_high_edge_very_high(void) {
    float temp = 100.0f;
    TEST_ASSERT_EQUAL_STRING("High", check_temperature_status(temp));
}

// NOTE ON main() FUNCTION TESTING:
// The `main()` function is the program's entry point and typically handles I/O
// and orchestrates other modules. Due to the strict constraints:
// 1. NO FUNCTION REDEFINITION
// 2. NO MOCKING FRAMEWORKS
// 3. TEST ACTUAL IMPLEMENTATIONS
// It is not feasible or appropriate to unit test `main()` directly within this
// Unity framework. Unit tests focus on isolated functions/units, not the program's
// entire execution flow which often involves system-level side effects (like printing).
// Therefore, tests are provided for the functions that `main()` depends on (`get_temperature_celsius`
// and `check_temperature_status`), assuming these are the actual "units" to be tested.


// --- Main Test Runner ---
int main(void) {
    UNITY_BEGIN();

    // Run tests for get_temperature_celsius
    RUN_TEST(test_get_temperature_celsius_returns_assumed_fixed_value);

    // Run tests for check_temperature_status
    RUN_TEST(test_check_temperature_status_normal_at_low_boundary);
    RUN_TEST(test_check_temperature_status_normal_mid_range);
    RUN_TEST(test_check_temperature_status_normal_at_high_boundary);
    RUN_TEST(test_check_temperature_status_low_just_below_boundary);
    RUN_TEST(test_check_temperature_status_low_general_value);
    RUN_TEST(test_check_temperature_status_low_edge_negative);
    RUN_TEST(test_check_temperature_status_low_edge_zero);
    RUN_TEST(test_check_temperature_status_high_just_above_boundary);
    RUN_TEST(test_check_temperature_status_high_general_value);
    RUN_TEST(test_check_temperature_status_high_edge_very_high);

    return UNITY_END();
}
