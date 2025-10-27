#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h" // Required for the stub
#include <stdlib.h> // For rand() related behavior in read_temperature_raw
#include <stdbool.h>
#include <string.h> // For string comparisons

// ========================================================================
// Stub for raw_to_celsius
// ========================================================================
static int raw_to_celsius_CallCount;
static int raw_to_celsius_InputRaw;
static float raw_to_celsius_Return;

float raw_to_celsius(int raw) {
    raw_to_celsius_CallCount++;
    raw_to_celsius_InputRaw = raw;
    return raw_to_celsius_Return;
}

// ========================================================================
// SetUp and TearDown functions
// ========================================================================
void setUp(void) {
    // Reset stub state
    raw_to_celsius_CallCount = 0;
    raw_to_celsius_InputRaw = 0;
    raw_to_celsius_Return = 0.0f;

    // Seed rand for predictable raw temperature values during specific tests if needed,
    // though the prompt implies testing actual rand() behavior for read_temperature_raw.
    // For read_temperature_raw's own test, we'll test the range, not specific values.
    // For get_temperature_celsius, we're relying on the stub for conversion.
    // We'll seed for read_temperature_raw when called by get_temperature_celsius for consistency.
    srand(0); // Ensure consistent random sequence across test runs
}

void tearDown(void) {
    // According to instructions, tearDown must reset ALL stub state variables.
    // Although setUp also resets, this ensures final cleanup.
    raw_to_celsius_CallCount = 0;
    raw_to_celsius_InputRaw = 0;
    raw_to_celsius_Return = 0.0f;
}

// ========================================================================
// Test Functions for read_temperature_raw
// ========================================================================

// Test that read_temperature_raw returns a value within the expected range [0, 1023]
void test_read_temperature_raw_returns_within_range(void) {
    for (int i = 0; i < 100; i++) { // Test multiple calls due to randomness
        int raw = read_temperature_raw();
        TEST_ASSERT_GREATER_OR_EQUAL_MESSAGE(0, raw, "Raw temperature should be >= 0");
        TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(1023, raw, "Raw temperature should be <= 1023");
    }
}

// ========================================================================
// Test Functions for validate_temperature_range
// ========================================================================

// Test with a temperature within the valid range
void test_validate_temperature_range_valid_normal(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

// Test with the minimum valid temperature
void test_validate_temperature_range_valid_min_edge(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f));
}

// Test with the maximum valid temperature
void test_validate_temperature_range_valid_max_edge(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

// Test with a temperature just below the minimum valid range
void test_validate_temperature_range_invalid_below_min(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-40.01f));
}

// Test with a temperature just above the maximum valid range
void test_validate_temperature_range_invalid_above_max(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.01f));
}

// Test with zero temperature
void test_validate_temperature_range_valid_zero(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
}

// ========================================================================
// Test Functions for check_temperature_status
// ========================================================================

// Test temperature in critical range (> 120.0f)
void test_check_temperature_status_critical(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.01f));
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(150.0f));
}

// Test temperature at the critical boundary (exactly 120.0f, should be HOT)
void test_check_temperature_status_hot_at_critical_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

// Test temperature in hot range (> 85.0f and <= 120.0f)
void test_check_temperature_status_hot(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.01f));
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(100.0f));
}

// Test temperature at the hot boundary (exactly 85.0f, should be NORMAL)
void test_check_temperature_status_normal_at_hot_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

// Test temperature in normal range (>= -10.0f and <= 85.0f)
void test_check_temperature_status_normal(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-9.99f));
}

// Test temperature at the cold boundary (exactly -10.0f, should be NORMAL)
void test_check_temperature_status_normal_at_cold_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-10.0f));
}

// Test temperature in cold range (< -10.0f)
void test_check_temperature_status_cold(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-10.01f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-20.0f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-40.0f));
}

// ========================================================================
// Test Functions for get_temperature_celsius
// ========================================================================

// Test that get_temperature_celsius calls raw_to_celsius and returns its result
void test_get_temperature_celsius_calls_converter_and_returns_result(void) {
    // Configure the stub to return a specific Celsius value
    raw_to_celsius_Return = 22.5f;

    // Call the function under test
    float result = get_temperature_celsius();

    // Assert that raw_to_celsius was called exactly once
    TEST_ASSERT_EQUAL(1, raw_to_celsius_CallCount);

    // Assert that the returned value matches the stub's configured return
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 22.5f, result);

    // Although read_temperature_raw is non-deterministic, we can verify
    // that its output was passed to raw_to_celsius and is within its expected range.
    TEST_ASSERT_GREATER_OR_EQUAL_MESSAGE(0, raw_to_celsius_InputRaw, "Raw input to converter should be >= 0");
    TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(1023, raw_to_celsius_InputRaw, "Raw input to converter should be <= 1023");
}

// Test with another configured stub return value
void test_get_temperature_celsius_calls_converter_with_another_result(void) {
    raw_to_celsius_Return = -5.0f;
    float result = get_temperature_celsius();
    TEST_ASSERT_EQUAL(1, raw_to_celsius_CallCount);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -5.0f, result);
    TEST_ASSERT_GREATER_OR_EQUAL_MESSAGE(0, raw_to_celsius_InputRaw, "Raw input to converter should be >= 0");
    TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(1023, raw_to_celsius_InputRaw, "Raw input to converter should be <= 1023");
}


// ========================================================================
// Main test runner
// ========================================================================
