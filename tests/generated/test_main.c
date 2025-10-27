```c
#include "unity.h"
#include "main.h"
#include "temp_sensor.h"
#include "temp_converter.h"

// Stubs

// get_temperature_celsius
static int get_temperature_celsius_CallCount = 0;
static float get_temperature_celsius_ReturnVal;

float get_temperature_celsius() {
    get_temperature_celsius_CallCount++;
    return get_temperature_celsius_ReturnVal;
}

void get_temperature_celsius_StubWithCallback(float (*callback)(void)) {
  // Not implemented in this example, but can be added if needed.
}

void reset_get_temperature_celsius() {
    get_temperature_celsius_CallCount = 0;
    get_temperature_celsius_ReturnVal = 0.0f;
}

void setUp(void) {
    reset_get_temperature_celsius();
}

void tearDown(void) {
}

void test_main_normal_temperature(void) {
    get_temperature_celsius_ReturnVal = 25.0f;
    int result = main();
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}

void test_main_low_temperature(void) {
    get_temperature_celsius_ReturnVal = -10.0f;
    int result = main();
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}

void test_main_high_temperature(void) {
    get_temperature_celsius_ReturnVal = 40.0f;
    int result = main();
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}

void test_main_zero_temperature(void) {
    get_temperature_celsius_ReturnVal = 0.0f;
    int result = main();
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}

void test_main_edge_temperature_below_freezing(void) {
  get_temperature_celsius_ReturnVal = -273.15f; //Absolute zero
  int result = main();
  TEST_ASSERT_EQUAL_INT(0, result);
  TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}

void test_main_edge_temperature_boiling(void) {
    get_temperature_celsius_ReturnVal = 100.0f;
    int result = main();
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}
```