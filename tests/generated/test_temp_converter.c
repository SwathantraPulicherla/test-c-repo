#include "unity.h"
#include "temp_converter.h"

// No stub functions are required for this C file based on the provided instructions.

void setUp(void) {
    // No stub state to initialize or reset, as no stubs are needed.
}

void tearDown(void) {
    // No stub state to clean up or reset, as no stubs are needed.
}

// region: Tests for raw_to_celsius

void test_raw_to_celsius_min_raw_value(void) {
    // raw_value = 0 should result in -40.0 C
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, raw_to_celsius(0));
}

void test_raw_to_celsius_max_raw_value(void) {
    // raw_value = 1023 should result in 125.0 C
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 125.0f, raw_to_celsius(1023));
}

void test_raw_to_celsius_mid_range_raw_value(void) {
    // raw_value = 512 (approx. half of 1023)
    // Calculation: (512 / 1023.0f) * 165.0f - 40.0f = 42.5806f
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 42.58f, raw_to_celsius(512));
}

void test_raw_to_celsius_zero_celsius_point(void) {
    // Calculate raw_value that results in 0 C:
    // 0 = (raw_value / 1023.0f) * 165.0f - 40.0f
    // raw_value = (40.0f / 165.0f) * 1023.0f approx 248
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, raw_to_celsius(248));
}

// endregion

// region: Tests for celsius_to_fahrenheit

void test_celsius_to_fahrenheit_freezing_point(void) {
    // 0 C should be 32 F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 32.0f, celsius_to_fahrenheit(0.0f));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    // 100 C should be 212 F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 212.0f, celsius_to_fahrenheit(100.0f));
}

void test_celsius_to_fahrenheit_body_temperature(void) {
    // 37 C should be 98.6 F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 98.6f, celsius_to_fahrenheit(37.0f));
}

void test_celsius_to_fahrenheit_negative_celsius(void) {
    // -40 C should be -40 F (a common conversion point)
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, celsius_to_fahrenheit(-40.0f));
}

void test_celsius_to_fahrenheit_room_temperature(void) {
    // 20 C should be 68 F
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 68.0f, celsius_to_fahrenheit(20.0f));
}

// endregion

// region: Tests for is_temperature_rising

void test_is_temperature_rising_true_well_above_threshold(void) {
    // current_temp (22.0) - prev_temp (20.0) = 2.0. Threshold (1.5). 2.0 > 1.5 is TRUE.
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 22.0f, 1.5f));
}

void test_is_temperature_rising_false_below_threshold(void) {
    // current_temp (21.0) - prev_temp (20.0) = 1.0. Threshold (1.5). 1.0 > 1.5 is FALSE.
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 21.0f, 1.5f));
}

void test_is_temperature_rising_false_at_threshold(void) {
    // current_temp (21.5) - prev_temp (20.0) = 1.5. Threshold (1.5). 1.5 > 1.5 is FALSE.
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 21.5f, 1.5f));
}

void test_is_temperature_rising_false_falling_temperature(void) {
    // current_temp (20.0) - prev_temp (25.0) = -5.0. Threshold (1.0). -5.0 > 1.0 is FALSE.
    TEST_ASSERT_FALSE(is_temperature_rising(25.0f, 20.0f, 1.0f));
}

void test_is_temperature_rising_false_equal_temperatures(void) {
    // current_temp (20.0) - prev_temp (20.0) = 0.0. Threshold (0.5). 0.0 > 0.5 is FALSE.
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.0f, 0.5f));
}

void test_is_temperature_rising_true_zero_threshold_rising(void) {
    // current_temp (20.1) - prev_temp (20.0) = 0.1. Threshold (0.0). 0.1 > 0.0 is TRUE.
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 20.1f, 0.0f));
}

void test_is_temperature_rising_false_zero_threshold_equal(void) {
    // current_temp (20.0) - prev_temp (20.0) = 0.0. Threshold (0.0). 0.0 > 0.0 is FALSE.
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.0f, 0.0f));
}

void test_is_temperature_rising_false_zero_threshold_falling(void) {
    // current_temp (19.9) - prev_temp (20.0) = -0.1. Threshold (0.0). -0.1 > 0.0 is FALSE.
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 19.9f, 0.0f));
}

// endregion

