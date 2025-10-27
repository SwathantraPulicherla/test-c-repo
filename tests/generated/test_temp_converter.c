```c
#include "unity.h"
#include "temp_converter.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_raw_to_celsius_normal_case(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 40.08, raw_to_celsius(500));
}

void test_raw_to_celsius_min_value(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01, -40.00, raw_to_celsius(0));
}

void test_raw_to_celsius_max_value(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 125.00, raw_to_celsius(1023));
}

void test_raw_to_celsius_negative_raw_value(void) {
    // Assuming negative raw values are not valid and will lead to unexpected results, but we can test for them
    TEST_ASSERT_FLOAT_WITHIN(0.01, -120.09, raw_to_celsius(-500)); // Result might be unexpected, but let's check it
}

void test_celsius_to_fahrenheit_normal_case(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 32.00, celsius_to_fahrenheit(0.0));
}

void test_celsius_to_fahrenheit_freezing_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 32.00, celsius_to_fahrenheit(0.0));
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 212.00, celsius_to_fahrenheit(100.0));
}

void test_celsius_to_fahrenheit_negative_celsius(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01, -40.00, celsius_to_fahrenheit(-40.0));
}

void test_celsius_to_fahrenheit_large_celsius(void) {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2156.00, celsius_to_fahrenheit(1157.0));
}

void test_is_temperature_rising_rising(void) {
    TEST_ASSERT_TRUE(is_temperature_rising(20.0, 25.0, 2.0));
}

void test_is_temperature_rising_not_rising(void) {
    TEST_ASSERT_FALSE(is_temperature_rising(25.0, 20.0, 2.0));
}

void test_is_temperature_rising_equal(void) {
    TEST_ASSERT_FALSE(is_temperature_rising(20.0, 20.0, 2.0));
}

void test_is_temperature_rising_threshold_exceeded(void) {
    TEST_ASSERT_TRUE(is_temperature_rising(20.0, 22.1, 2.0));
}

void test_is_temperature_rising_negative_temperatures(void) {
    TEST_ASSERT_TRUE(is_temperature_rising(-10.0, -5.0, 3.0));
}

void test_is_temperature_rising_negative_threshold(void) {
     TEST_ASSERT_TRUE(is_temperature_rising(20.0, 25.0, -2.0));
}

void test_is_temperature_rising_zero_threshold(void) {
    TEST_ASSERT_TRUE(is_temperature_rising(20.0, 21.0, 0.0));
    TEST_ASSERT_FALSE(is_temperature_rising(20.0, 20.0, 0.0));
    TEST_ASSERT_FALSE(is_temperature_rising(20.0, 19.0, 0.0));
}
```