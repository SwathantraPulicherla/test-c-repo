#include "unity.h"
#include "temp_converter.h"
#include <stdbool.h> // For bool type

// No stub functions are required for this C file.

void setUp(void) {
    // No setup needed as there are no stubs or global state to initialize.
}

void tearDown(void) {
    // No teardown needed as there are no stubs or global state to reset.
}

// Test cases for raw_to_celsius
void test_raw_to_celsius_min_value(void) {
    int raw_value = 0;
    float expected_celsius = -40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023.0f / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_range(void) {
    int raw_value = 512;
    float expected_celsius = (512.0f / 1023.0f) * 165.0f - 40.0f; // Approx 42.68 C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_another_value(void) {
    int raw_value = 255;
    float expected_celsius = (255.0f / 1023.0f) * 165.0f - 40.0f; // Approx 1.05 C
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

// Test cases for celsius_to_fahrenheit
void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_f = 32.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_f = 212.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_negative_value(void) {
    float temp_c = -40.0f; // Point where Celsius and Fahrenheit are equal
    float expected_f = -40.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_f = 77.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_f, actual_f);
}

// Test cases for is_temperature_rising
void test_is_temperature_rising_true_above_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 0.2f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_at_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.2f;
    float threshold = 0.2f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // Should be false because of '>' not '>='
}

void test_is_temperature_rising_false_below_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.1f;
    float threshold = 0.2f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_falling(void) {
    float prev_temp = 25.0f;
    float current_temp = 24.5f;
    float threshold = 0.1f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_no_change(void) {
    float prev_temp = 22.0f;
    float current_temp = 22.0f;
    float threshold = 0.05f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_true_zero_threshold_rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.01f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_zero_threshold_no_change(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

