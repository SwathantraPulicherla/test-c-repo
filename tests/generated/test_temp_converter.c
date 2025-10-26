#include "unity.h"
#include "temp_converter.h"
#include <math.h> // For fabs

// Define a tolerance for float comparisons
#define FLOAT_TOLERANCE 0.0001f

void setUp(void) {
    // This function is called before each test
}

void tearDown(void) {
    // This function is called after each test
}

// Test cases for raw_to_celsius

void test_raw_to_celsius_min_raw_value(void) {
    float expected_celsius = -40.0f;
    float actual_celsius = raw_to_celsius(0);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_max_raw_value(void) {
    float expected_celsius = 125.0f;
    float actual_celsius = raw_to_celsius(1023);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_mid_raw_value(void) {
    // (512 / 1023.0) * 165.0 - 40.0 = 42.58064516
    float expected_celsius = 42.5806f;
    float actual_celsius = raw_to_celsius(512);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

void test_raw_to_celsius_negative_raw_value_edge_case(void) {
    // Input is int, but checking robustness for unexpected negative values.
    // The current formula will yield a value even for negative raw_value.
    // For -1: (-1 / 1023.0) * 165.0 - 40.0 = -0.16129 - 40.0 = -40.16129
    float expected_celsius = -40.16129f;
    float actual_celsius = raw_to_celsius(-1);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_celsius, actual_celsius);
}

// Test cases for celsius_to_fahrenheit

void test_celsius_to_fahrenheit_zero_celsius(void) {
    float expected_fahrenheit = 32.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float expected_fahrenheit = 212.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(100.0f);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_freezing_point(void) {
    float expected_fahrenheit = 32.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_negative_celsius(void) {
    float expected_fahrenheit = -4.0f; // -20 C = -4 F
    float actual_fahrenheit = celsius_to_fahrenheit(-20.0f);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_absolute_zero(void) {
    // -273.15 C = -459.67 F
    float expected_fahrenheit = -459.67f;
    float actual_fahrenheit = celsius_to_fahrenheit(-273.15f);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

void test_celsius_to_fahrenheit_identical_value(void) {
    // -40 C is -40 F
    float expected_fahrenheit = -40.0f;
    float actual_fahrenheit = celsius_to_fahrenheit(-40.0f);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, expected_fahrenheit, actual_fahrenheit);
}

// Test cases for is_temperature_rising

void test_is_temperature_rising_true(void) {
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 25.0f, 2.0f)); // 5 > 2
}

void test_is_temperature_rising_false_falling(void) {
    TEST_ASSERT_FALSE(is_temperature_rising(25.0f, 20.0f, 2.0f)); // -5 > 2 is false
}

void test_is_temperature_rising_false_stable(void) {
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.0f, 2.0f)); // 0 > 2 is false
}

void test_is_temperature_rising_false_equal_to_threshold(void) {
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 22.0f, 2.0f)); // 2 > 2 is false
}

void test_is_temperature_rising_true_just_above_threshold(void) {
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 22.0001f, 2.0f)); // 2.0001 > 2 is true
}

void test_is_temperature_rising_zero_threshold_rising(void) {
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 20.001f, 0.0f)); // 0.001 > 0 is true
}

void test_is_temperature_rising_zero_threshold_stable(void) {
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 20.0f, 0.0f)); // 0 > 0 is false
}

void test_is_temperature_rising_zero_threshold_falling(void) {
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 19.999f, 0.0f)); // -0.001 > 0 is false
}

void test_is_temperature_rising_negative_threshold(void) {
    // If threshold is negative, (current - prev) > negative threshold can be true even if temp is falling
    TEST_ASSERT_TRUE(is_temperature_rising(20.0f, 19.0f, -2.0f)); // -1 > -2 is true
    TEST_ASSERT_FALSE(is_temperature_rising(20.0f, 19.0f, -0.5f)); // -1 > -0.5 is false
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_raw_to_celsius_min_raw_value);
    RUN_TEST(test_raw_to_celsius_max_raw_value);
    RUN_TEST(test_raw_to_celsius_mid_raw_value);
    RUN_TEST(test_raw_to_celsius_negative_raw_value_edge_case);

    RUN_TEST(test_celsius_to_fahrenheit_zero_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_boiling_point);
    RUN_TEST(test_celsius_to_fahrenheit_freezing_point);
    RUN_TEST(test_celsius_to_fahrenheit_negative_celsius);
    RUN_TEST(test_celsius_to_fahrenheit_absolute_zero);
    RUN_TEST(test_celsius_to_fahrenheit_identical_value);

    RUN_TEST(test_is_temperature_rising_true);
    RUN_TEST(test_is_temperature_rising_false_falling);
    RUN_TEST(test_is_temperature_rising_false_stable);
    RUN_TEST(test_is_temperature_rising_false_equal_to_threshold);
    RUN_TEST(test_is_temperature_rising_true_just_above_threshold);
    RUN_TEST(test_is_temperature_rising_zero_threshold_rising);
    RUN_TEST(test_is_temperature_rising_zero_threshold_stable);
    RUN_TEST(test_is_temperature_rising_zero_threshold_falling);
    RUN_TEST(test_is_temperature_rising_negative_threshold);

    return UNITY_END();
}