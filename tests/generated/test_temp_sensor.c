#include "unity.h"
#include "temp_sensor.h" // The module under test
#include <stdbool.h>     // For bool type
#include <string.h>      // For TEST_ASSERT_EQUAL_STRING
#include <stdlib.h>      // For rand(), though not directly called in test, it's used by UUT

// ======================================================================
// STUBS for external dependencies
// ======================================================================

// Stub for raw_to_celsius function from temp_converter.h
static int raw_to_celsius_CallCount;
static float raw_to_celsius_Return;
static int raw_to_celsius_LastRawArg; // Stores the last 'raw' argument passed to the stub

float raw_to_celsius(int raw) {
    raw_to_celsius_CallCount++;
    raw_to_celsius_LastRawArg = raw;
    return raw_to_celsius_Return;
}

// Helper function to reset stub state
void reset_temp_converter_stubs(void) {
    raw_to_celsius_CallCount = 0;
    raw_to_celsius_Return = 0.0f;
    raw_to_celsius_LastRawArg = 0;
}

// ======================================================================
// UNITY TEST FRAMEWORK FUNCTIONS
// ======================================================================

void setUp(void) {
    // Reset stubs before each test
    reset_temp_converter_stubs();
}

void tearDown(void) {
    // Nothing to tear down for this module
}

// ======================================================================
// TEST CASES for read_temperature_raw
// ======================================================================

void test_read_temperature_raw_returnsValueWithinExpectedRange(void) {
    // Since read_temperature_raw uses rand() % 1024,
    // we can only reliably test that the return value is within the expected range.
    int raw_value = read_temperature_raw();
    TEST_ASSERT_TRUE(raw_value >= 0);
    TEST_ASSERT_TRUE(raw_value <= 1023); // 1024 values from 0 to 1023
}

// ======================================================================
// TEST CASES for validate_temperature_range
// ======================================================================

void test_validate_temperature_range_withinValidRange(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
    TEST_ASSERT_TRUE(validate_temperature_range(50.0f));
}

void test_validate_temperature_range_atLowerEdge(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f));
}

void test_validate_temperature_range_atUpperEdge(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_belowLowerEdge(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-40.1f));
    TEST_ASSERT_FALSE(validate_temperature_range(-50.0f));
}

void test_validate_temperature_range_aboveUpperEdge(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
    TEST_ASSERT_FALSE(validate_temperature_range(130.0f));
}

// ======================================================================
// TEST CASES for check_temperature_status (covering "else if" and "else" branches)
// ======================================================================

void test_check_temperature_status_critical(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f));
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(150.0f));
}

void test_check_temperature_status_hot(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f)); // Upper boundary of HOT
}

void test_check_temperature_status_cold(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-10.1f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-40.0f)); // Lower boundary
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-50.0f));
}

void test_check_temperature_status_normal(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(50.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-10.0f)); // Lower boundary of NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));  // Upper boundary of NORMAL
}

// ======================================================================
// TEST CASES for get_temperature_celsius
// ======================================================================

void test_get_temperature_celsius_callsRawToCelsiusAndReturnsConvertedValue(void) {
    // Configure the stub to return a specific Celsius value
    raw_to_celsius_Return = 25.5f;

    float result = get_temperature_celsius();

    // Verify that raw_to_celsius was called exactly once
    TEST_ASSERT_EQUAL_INT(1, raw_to_celsius_CallCount);

    // Verify that the result is what the stub returned
    TEST_ASSERT_EQUAL_FLOAT(25.5f, result);

    // Optionally, verify that raw_to_celsius was called with a raw value in the expected range
    TEST_ASSERT_TRUE(raw_to_celsius_LastRawArg >= 0);
    TEST_ASSERT_TRUE(raw_to_celsius_LastRawArg <= 1023);
}

void test_get_temperature_celsius_anotherConversionValue(void) {
    raw_to_celsius_Return = -15.2f;

    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL_INT(1, raw_to_celsius_CallCount);
    TEST_ASSERT_EQUAL_FLOAT(-15.2f, result);
    TEST_ASSERT_TRUE(raw_to_celsius_LastRawArg >= 0);
    TEST_ASSERT_TRUE(raw_to_celsius_LastRawArg <= 1023);
}

// ======================================================================
// MAIN function to run all tests
// ======================================================================

int main(void) {
    UNITY_BEGIN();

    // Run tests for read_temperature_raw
    RUN_TEST(test_read_temperature_raw_returnsValueWithinExpectedRange);

    // Run tests for validate_temperature_range
    RUN_TEST(test_validate_temperature_range_withinValidRange);
    RUN_TEST(test_validate_temperature_range_atLowerEdge);
    RUN_TEST(test_validate_temperature_range_atUpperEdge);
    RUN_TEST(test_validate_temperature_range_belowLowerEdge);
    RUN_TEST(test_validate_temperature_range_aboveUpperEdge);

    // Run tests for check_temperature_status
    RUN_TEST(test_check_temperature_status_critical);
    RUN_TEST(test_check_temperature_status_hot);
    RUN_TEST(test_check_temperature_status_cold);
    RUN_TEST(test_check_temperature_status_normal);

    // Run tests for get_temperature_celsius
    RUN_TEST(test_get_temperature_celsius_callsRawToCelsiusAndReturnsConvertedValue);
    RUN_TEST(test_get_temperature_celsius_anotherConversionValue);

    return UNITY_END();
}