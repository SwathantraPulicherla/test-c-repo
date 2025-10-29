#include "unity.h"
#include "temp_converter.h" // Include the header for the module under test
#include <stdbool.h>

// --- Stubs for functions that need stubs ---
// No stubs are needed for this module, as per the "FUNCTIONS THAT NEED STUBS" section.
// This section is kept for completeness as per requirements, but will be empty.

// --- Test Setup and Teardown ---
void setUp(void) {
    // Reset any stub state here, if stubs were present.
}

void tearDown(void) {
    // Clean up any resources here, if necessary.
    // Reset any stub state here, if stubs were present.
}

// --- Test Cases for raw_to_celsius ---

// Test minimum raw value (0)
void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = -40.0f; // (0 / 1023.0f) * 165.0f - 40.0f = -40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// Test maximum raw value (1023)
void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// Test mid-range raw value (512, approximately half)
void test_raw_to_celsius_mid_range_value(void) {
    int raw_value = 512;
    float expected_celsius = (512.0f / 1023.0f) * 165.0f - 40.0f; // Approx 42.15 C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// Test another specific raw value (e.g., to get 0C)
void test_raw_to_celsius_zero_celsius(void) {
    // Solve for raw_value when result is 0: (raw_value / 1023.0f) * 165.0f - 40.0f = 0
    // (raw_value / 1023.0f) * 165.0f = 40.0f
    // raw_value / 1023.0f = 40.0f / 165.0f
    // raw_value = (40.0f / 165.0f) * 1023.0f = 248.0f
    int raw_value = 248; 
    float expected_celsius = 0.0f; 
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// Test edge case slightly above min raw
void test_raw_to_celsius_small_positive_raw(void) {
    int raw_value = 1;
    float expected_celsius = (1.0f / 1023.0f) * 165.0f - 40.0f; // Approx -39.83 C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}


// --- Test Cases for celsius_to_fahrenheit ---

// Test freezing point (0 C)
void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// Test boiling point (100 C)
void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = (100.0f * 9.0f / 5.0f) + 32.0f; // 212.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// Test body temperature (37 C)
void test_celsius_to_fahrenheit_body_temp(void) {
    float temp_c = 37.0f;
    float expected_fahrenheit = (37.0f * 9.0f / 5.0f) + 32.0f; // 98.6f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// Test negative Celsius value (-10 C)
void test_celsius_to_fahrenheit_negative_celsius(void) {
    float temp_c = -10.0f;
    float expected_fahrenheit = (-10.0f * 9.0f / 5.0f) + 32.0f; // 14.0f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// Test very low Celsius value (-40 C, where C == F)
void test_celsius_to_fahrenheit_minus_40_c(void) {
    float temp_c = -40.0f;
    float expected_fahrenheit = -40.0f; // (-40 * 9/5) + 32 = -72 + 32 = -40
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

// Test a fractional Celsius value
void test_celsius_to_fahrenheit_fractional_celsius(void) {
    float temp_c = 25.5f;
    float expected_fahrenheit = (25.5f * 9.0f / 5.0f) + 32.0f; // 77.9f
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}


// --- Test Cases for is_temperature_rising ---

// Test when temperature is clearly rising above threshold
void test_is_temperature_rising_clear_rise(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

// Test when temperature is rising but below threshold
void test_is_temperature_rising_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

// Test when temperature is exactly at threshold
void test_is_temperature_rising_at_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // (22.0 - 20.0) > 2.0 is 2.0 > 2.0, which is false
}

// Test when temperature is falling
void test_is_temperature_rising_falling(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 2.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

// Test when temperature is stable (no change)
void test_is_temperature_rising_stable(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.5f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

// Test with zero threshold and rising temperature
void test_is_temperature_rising_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // (20.1 - 20.0) > 0.0 is 0.1 > 0.0, which is true
}

// Test with zero threshold and stable temperature
void test_is_temperature_rising_zero_threshold_stable(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // (20.0 - 20.0) > 0.0 is 0.0 > 0.0, which is false
}

// Test with negative threshold (unlikely, but covers the math)
void test_is_temperature_rising_negative_threshold_rise(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = -0.5f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // (21.0 - 20.0) > -0.5 is 1.0 > -0.5, which is true
}

// Test with negative threshold and falling temperature
void test_is_temperature_rising_negative_threshold_fall(void) {
    float prev_temp = 21.0f;
    float current_temp = 20.0f;
    float threshold = -0.5f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // (20.0 - 21.0) > -0.5 is -1.0 > -0.5, which is false
}

// --- Main Test Runner ---
