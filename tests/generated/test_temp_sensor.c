#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"
#include <stdlib.h>
#include <stdbool.h>

// Stub for raw_to_celsius
static int raw_to_celsius_CallCount;
static float raw_to_celsius_Return;

float raw_to_celsius(int raw_value) {
    raw_to_celsius_CallCount++;
    (void)raw_value; // Suppress unused parameter warning
    return raw_to_celsius_Return;
}

void setUp(void) {
    raw_to_celsius_CallCount = 0;
    raw_to_celsius_Return = 0.0f;
}

void tearDown(void) {
    raw_to_celsius_CallCount = 0;
    raw_to_celsius_Return = 0.0f;
}

void test_read_temperature_raw_ReturnsWithinRange(void) {
    // Test multiple times to ensure random output is within expected range
    for (int i = 0; i < 100; i++) {
        int raw = read_temperature_raw();
        TEST_ASSERT_TRUE(raw >= 0);
        TEST_ASSERT_TRUE(raw < 1024); // rand() % 1024 gives values from 0 to 1023
    }
}

void test_validate_temperature_range_ValidMin(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f));
}

void test_validate_temperature_range_ValidMax(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void test_validate_temperature_range_ValidMid(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(50.0f));
}

void test_validate_temperature_range_BelowMin(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-40.1f));
}

void test_validate_temperature_range_AboveMax(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void test_check_temperature_status_Critical(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.1f));
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(200.0f));
}

void test_check_temperature_status_Hot(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.1f));
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(110.0f));
}

void test_check_temperature_status_Cold(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-10.1f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-50.0f));
}

void test_check_temperature_status_Normal_JustBelowCritical(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(120.0f));
}

void test_check_temperature_status_Normal_JustBelowHot(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

void test_check_temperature_status_Normal_JustAboveCold(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-10.0f));
}

void test_check_temperature_status_Normal_MidRange(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(50.0f));
}

void test_get_temperature_celsius_ReturnsConvertedValue(void) {
    raw_to_celsius_Return = 25.5f;
    float temp_c = get_temperature_celsius();
    TEST_ASSERT_EQUAL(1, raw_to_celsius_CallCount);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 25.5f, temp_c);
}

void test_get_temperature_celsius_DifferentConversion(void) {
    raw_to_celsius_Return = -5.0f;
    float temp_c = get_temperature_celsius();
    TEST_ASSERT_EQUAL(1, raw_to_celsius_CallCount);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -5.0f, temp_c);
}

