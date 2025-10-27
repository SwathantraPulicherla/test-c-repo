#include "unity.h"
#include "temp_converter.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_raw_to_celsius_normal_case(void) {
    float celsius = raw_to_celsius(512);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 43.33f, celsius);
}

void test_raw_to_celsius_min_value(void) {
    float celsius = raw_to_celsius(0);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, celsius);
}

void test_raw_to_celsius_max_value(void) {
    float celsius = raw_to_celsius(1023);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 125.0f, celsius);
}

void test_raw_to_celsius_at_zero(void) {
    float celsius = raw_to_celsius(246);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.03f, celsius);
}

void test_celsius_to_fahrenheit_normal_case(void) {
    float fahrenheit = celsius_to_fahrenheit(25.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 77.0f, fahrenheit);
}

void test_celsius_to_fahrenheit_freezing_point(void) {
    float fahrenheit = celsius_to_fahrenheit(0.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 32.0f, fahrenheit);
}

void test_celsius_to_fahrenheit_boiling_point(void) {
    float fahrenheit = celsius_to_fahrenheit(100.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 212.0f, fahrenheit);
}

void test_celsius_to_fahrenheit_negative_temp(void) {
    float fahrenheit = celsius_to_fahrenheit(-40.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -40.0f, fahrenheit);
}

void test_is_temperature_rising_rising(void) {
    bool rising = is_temperature_rising(20.0f, 25.0f, 2.0f);
    TEST_ASSERT_TRUE(rising);
}

void test_is_temperature_rising_not_rising(void) {
    bool rising = is_temperature_rising(20.0f, 21.0f, 2.0f);
    TEST_ASSERT_FALSE(rising);
}

void test_is_temperature_rising_equal(void) {
    bool rising = is_temperature_rising(20.0f, 20.0f, 2.0f);
    TEST_ASSERT_FALSE(rising);
}

void test_is_temperature_rising_negative_temps(void) {
   bool rising = is_temperature_rising(-10.0f, -5.0f, 2.0f);
   TEST_ASSERT_TRUE(rising);
}

void test_is_temperature_rising_threshold_zero(void) {
    bool rising = is_temperature_rising(20.0f, 21.0f, 0.0f);
    TEST_ASSERT_TRUE(rising);
}
