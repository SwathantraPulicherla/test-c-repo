#include "unity.h"
#include "temp_converter.h"

// Define a tolerance for float comparisons
#define FLOAT_TOLERANCE 0.01f

// No stubs needed according to the prompt

void setUp(void) {
    // No stubs to reset for this module
}

void tearDown(void) {
    // No stubs to reset for this module
}

// region: raw_to_celsius tests
void test_raw_to_celsius_min_raw_value(void) {
    int raw_value = 0;
    float expected_celsius = -40.0f; // (0 / 1023.0f) * 165.0f - 40.0f = -40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 125.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_raw_value(void) {
    int raw_value = 512;
    // (512 / 1023.0f) * 165.0f - 40.0f = 0.50048875855 * 165.0f - 40.0f = 82.58064516 - 40.0f = 42.58064516
    float expected_celsius = 42.58f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_specific_value(void) {
    int raw_value = 256;
    // (256 / 1023.0f) * 165.0f - 40.0f = 0.250244379 * 165.0f - 40.0f = 41.29032258 - 40.0f = 1.29032258
    float expected_celsius = 1.29f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}
// endregion

// region: celsius_to_fahrenheit tests
void test_celsius_to_fahrenheit_freezing_point(void) {
    float temp_c = 0.0f;
    float expected_fahrenheit = 32.0f; // (0 * 9/5) + 32 = 32
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float temp_c = 100.0f;
    float expected_fahrenheit = 212.0f; // (100 * 9/5) + 32 = 180 + 32 = 212
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    float temp_c = 25.0f;
    float expected_fahrenheit = 77.0f; // (25 * 9/5) + 32 = 45 + 32 = 77
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_value(void) {
    float temp_c = -40.0f;
    float expected_fahrenheit = -40.0f; // (-40 * 9/5) + 32 = -72 + 32 = -40 (C and F are equal)
    float actual_fahrenheit = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}
// endregion

// region: is_temperature_rising tests
void test_is_temperature_rising_true_scenario(void) {
    float prev_temp = 20.0f;
    float current_temp = 25.0f;
    float threshold = 3.0f; // (25 - 20) > 3 => 5 > 3 => TRUE
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_not_rising_enough(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 3.0f; // (22 - 20) > 3 => 2 > 3 => FALSE
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_falling(void) {
    float prev_temp = 25.0f;
    float current_temp = 20.0f;
    float threshold = 3.0f; // (20 - 25) > 3 => -5 > 3 => FALSE
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_equal_to_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 23.0f;
    float threshold = 3.0f; // (23 - 20) > 3 => 3 > 3 => FALSE (strictly greater than)
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_false_no_change_zero_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f; // (20 - 20) > 0 => 0 > 0 => FALSE
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_true_slight_rise_zero_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.01f;
    float threshold = 0.0f; // (20.01 - 20) > 0 => 0.01 > 0 => TRUE
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_slight_drop_zero_threshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.99f;
    float threshold = 0.0f; // (19.99 - 20) > 0 => -0.01 > 0 => FALSE
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

void test_is_temperature_rising_true_large_positive_threshold(void) {
    float prev_temp = 10.0f;
    float current_temp = 30.0f;
    float threshold = 15.0f; // (30 - 10) > 15 => 20 > 15 => TRUE
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

void test_is_temperature_rising_false_large_negative_threshold_rise(void) {
    float prev_temp = 10.0f;
    float current_temp = 12.0f;
    float threshold = -5.0f; // (12 - 10) > -5 => 2 > -5 => TRUE (always true if threshold is negative and temp rises or stays same)
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}
// endregion

