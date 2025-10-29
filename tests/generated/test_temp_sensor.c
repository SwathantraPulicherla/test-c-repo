#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"
#include <stdbool.h>
#include <stdlib.h> // For rand()

// ====================================================================
// Stub functions for dependencies
// ====================================================================

static int raw_to_celsius_CallCount;
static float raw_to_celsius_Return;

float raw_to_celsius(int raw_value) {
    raw_to_celsius_CallCount++;
    // In this stub, we return a pre-configured value, ignoring the input for testing purposes.
    (void)raw_value; // Suppress unused parameter warning
    return raw_to_celsius_Return;
}

// ====================================================================
// SetUp and TearDown functions
// ====================================================================

void setUp(void) {
    // Reset all stub state for each test
    raw_to_celsius_CallCount = 0;
    raw_to_celsius_Return = 0.0f; // Default return value
}

void tearDown(void) {
    // Nothing needed here as setUp handles all stub resets for each test.
}

// ====================================================================
// Test functions for temp_sensor.c
// ====================================================================

// Test for read_temperature_raw
void test_read_temperature_raw_returns_within_valid_range(void) {
    // Since rand() is non-deterministic, we check that the return value
    // is within the expected range [0, 1023] based on `rand() % 1024`.
    int i;
    for (i = 0; i < 5; i++) { // Test a few times to increase confidence
        int val = read_temperature_raw();
        TEST_ASSERT_TRUE_MESSAGE(val >= 0, "read_temperature_raw returned value below 0");
        TEST_ASSERT_TRUE_MESSAGE(val < 1024, "read_temperature_raw returned value 1024 or above");
    }
}

// Tests for validate_temperature_range
void test_validate_temperature_range_valid_within_bounds(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
    TEST_ASSERT_TRUE(validate_temperature_range(100.0f));
}

void test_validate_temperature_range_valid_min_edge(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f));
}

void test_validate_temperature_range_valid_max_edge(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_invalid_below_min(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-40.1f));
    TEST_ASSERT_FALSE(validate_temperature_range(-50.0f));
}

void test_validate_temperature_range_invalid_above_max(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
    TEST_ASSERT_FALSE(validate_temperature_range(150.0f));
}

// Tests for check_temperature_status (covering else if conditions)
void test_check_temperature_status_critical_high(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(130.0f));
}

void test_check_temperature_status_hot_above_85(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f)); // Max for HOT before CRITICAL
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(100.0f));
}

void test_check_temperature_status_cold_below_neg10(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-10.1f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-20.0f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-40.0f)); // Min valid range, still COLD
}

void test_check_temperature_status_normal_range(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-10.0f)); // Min for NORMAL
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f)); // Max for NORMAL
}

// Tests for get_temperature_celsius
void test_get_temperature_celsius_uses_converter_stub(void) {
    // Configure stub to return a specific value
    raw_to_celsius_Return = 37.5f;

    float result = get_temperature_celsius();

    // Verify that the stub function was called exactly once
    TEST_ASSERT_EQUAL(1, raw_to_celsius_CallCount);

    // Verify that get_temperature_celsius returns the value provided by the stub
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 37.5f, result);
}

void test_get_temperature_celsius_with_different_stub_value(void) {
    // Configure stub for another value
    raw_to_celsius_Return = -5.2f;

    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL(1, raw_to_celsius_CallCount);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -5.2f, result);
}

// ====================================================================
// Main Test Runner
// ====================================================================

