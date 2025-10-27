#include "unity.h"
#include "temp_converter.h"
#include <stdbool.h> // For bool type

// No stubs are required for this C file according to the prompt.

void setUp(void) {
    // No stub state to reset for this module.
}

void tearDown(void) {
    // No stub state to reset for this module.
}

// region: Tests for raw_to_celsius
void test_raw_to_celsius_min_value(void) {
    // raw_value = 0 should result in ((0/1023.0f) * 165.0f) - 40.0f = -40.0f
    float expected_celsius = -40.0f;
    float actual_celsius = raw_to_celsius(0);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_value(void) {
    // raw_value = 1023 should result in ((1023/1023.0f) * 165.0f) - 40.0f = 165.0f - 40.0f = 125.0f
    float expected_celsius = 125.0f;
    float actual_celsius = raw_to_celsius(1023);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_value(void) {
    // raw_value = 512 should result in ((512/1023.0f) * 165.0f) - 40.0f approx 41.77
    float expected_celsius = (512.0f / 1023.0f) * 165.0f - 40.0f;
    float actual_celsius = raw_to_celsius(512);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_another_value(void) {
    // raw_value = 250
    float expected_celsius = (250.0f / 1023.0f) * 165.0f - 40.0f;
    float actual_celsius = raw_to_celsius(250);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_celsius, actual_celsius);
}
// endregion

// region: Tests for celsius_to_fahrenheit
void test_celsius_to_fahrenheit_freezing_point(void) {
    // 0°C should be 32°F
    float expected_fahrenheit = 32.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    // 100°C should be 212°F
    float expected_fahrenheit = 212.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(100.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_forty(void) {
    // -40°C should be -40°F
    float expected_fahrenheit = -40.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(-40.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_room_temp(void) {
    // 25°C should be 77°F
    float expected_fahrenheit = (25.0f * 9.0f / 5.0f) + 32.0f; // 45 + 32 = 77
    float actual_fahrenheit = celsius_to_fahrenheit(25.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_zero_value(void) {
    // Test with 0.0f Celsius
    float expected_fahrenheit = 32.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_fahrenheit, actual_fahrenheit);
}
// endregion

// region: Tests for is_temperature_rising
void test_is_temperature_rising_true(void) {
    // Current - Prev > Threshold
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 22.0f, 1.0f));
}

void test_is_temperature_rising_false_equal_to_threshold(void) {
    // Current - Prev == Threshold
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 21.0f, 1.0f));
}

void test_is_temperature_rising_false_less_than_threshold(void) {
    // Current - Prev < Threshold
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.5f, 1.0f));
}

void test_is_temperature_rising_false_falling_temp(void) {
    // Current < Prev
    TEST_ASSERT_FALSE(is_temperature_rising(22.0f, 20.0f, 1.0f));
}

void test_is_temperature_rising_false_stable_temp(void) {
    // Current == Prev
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.0f, 1.0f));
}

void test_is_temperature_rising_zero_threshold_true(void) {
    // Current - Prev > 0
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 20.1f, 0.0f));
}

void test_is_temperature_rising_zero_threshold_false_stable(void) {
    // Current - Prev == 0
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.0f, 0.0f));
}

void test_is_temperature_rising_negative_threshold_true(void) {
    // A rise of 0.5 degrees is greater than a -1.0 threshold
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 20.5f, -1.0f));
}

void test_is_temperature_rising_negative_threshold_false(void) {
    // A fall of 0.5 degrees is NOT greater than a -0.2 threshold (it's less than)
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 19.5f, -0.2f));
}

void test_is_temperature_rising_small_rise(void) {
    TEST_ASSERT_TRUE(is_temperature_rising(10.0f, 10.02f, 0.01f));
}

void test_is_temperature_rising_very_small_rise_fails(void) {
    TEST_ASSERT_FALSE(is_temperature_rising(10.0f, 10.005f, 0.01f));
}
// endregion

