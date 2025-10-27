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
  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, raw_to_celsius(246));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 25.0, raw_to_celsius(404));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 50.0, raw_to_celsius(562));
}

void test_raw_to_celsius_edge_cases(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, -40.0, raw_to_celsius(0));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 125.0, raw_to_celsius(1023));
}

void test_raw_to_celsius_min_max_values(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, -40.0, raw_to_celsius(0));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 125.0, raw_to_celsius(1023));
}

void test_celsius_to_fahrenheit_normal_case(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, 32.0, celsius_to_fahrenheit(0.0));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 68.0, celsius_to_fahrenheit(20.0));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 212.0, celsius_to_fahrenheit(100.0));
}

void test_celsius_to_fahrenheit_edge_cases(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, -40.0, celsius_to_fahrenheit(-40.0));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 212.0, celsius_to_fahrenheit(100.0));
}

void test_celsius_to_fahrenheit_min_max_values(void) {
  TEST_ASSERT_FLOAT_WITHIN(0.01, -459.67, celsius_to_fahrenheit(-273.15)); // Absolute zero
  TEST_ASSERT_FLOAT_WITHIN(0.01, 212.0, celsius_to_fahrenheit(100.0));     // Boiling point
}

void test_is_temperature_rising_rising(void) {
  TEST_ASSERT_TRUE(is_temperature_rising(20.0, 25.0, 2.0));
}

void test_is_temperature_rising_not_rising(void) {
  TEST_ASSERT_FALSE(is_temperature_rising(20.0, 21.0, 2.0));
}

void test_is_temperature_rising_equal(void) {
  TEST_ASSERT_FALSE(is_temperature_rising(20.0, 20.0, 2.0));
}

void test_is_temperature_rising_falling(void) {
  TEST_ASSERT_FALSE(is_temperature_rising(20.0, 15.0, 2.0));
}

void test_is_temperature_rising_threshold_exact(void) {
  TEST_ASSERT_FALSE(is_temperature_rising(20.0, 22.0, 2.0));
}

void test_is_temperature_rising_negative_temps(void) {
  TEST_ASSERT_TRUE(is_temperature_rising(-10.0, -5.0, 2.0));
  TEST_ASSERT_FALSE(is_temperature_rising(-10.0, -12.0, 2.0));
}
```