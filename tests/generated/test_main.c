#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"

// Stubs
static int get_temperature_celsius_call_count;
static float get_temperature_celsius_return_value;

float get_temperature_celsius() {
  get_temperature_celsius_call_count++;
  return get_temperature_celsius_return_value;
}


void setUp(void) {
    get_temperature_celsius_call_count = 0;
    get_temperature_celsius_return_value = 0.0f;
}

void tearDown(void) {
}

void test_main_normal_temperature(void) {
    get_temperature_celsius_return_value = 25.0f;
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 25.0f, get_temperature_celsius());
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_call_count);
}

void test_main_freezing_temperature(void) {
    get_temperature_celsius_return_value = 0.0f;
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, get_temperature_celsius());
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_call_count);
}

void test_main_below_freezing_temperature(void) {
    get_temperature_celsius_return_value = -10.0f;
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -10.0f, get_temperature_celsius());
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_call_count);
}

void test_main_high_temperature(void) {
    get_temperature_celsius_return_value = 40.0f;
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 40.0f, get_temperature_celsius());
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_call_count);
}

void test_main_extreme_low_temperature(void) {
    get_temperature_celsius_return_value = -50.0f;
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -50.0f, get_temperature_celsius());
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_call_count);
}

void test_main_extreme_high_temperature(void) {
    get_temperature_celsius_return_value = 100.0f;
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 100.0f, get_temperature_celsius());
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_call_count);
}
