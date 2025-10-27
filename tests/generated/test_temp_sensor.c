#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"
#include <stdbool.h>
#include <stdlib.h> // For rand() in source code

// --- Stub for raw_to_celsius ---
static int raw_to_celsius_CalledCount;
static float raw_to_celsius_Return;
static int raw_to_celsius_RawArg_actual; // To store the argument passed to the stub

float raw_to_celsius(int raw) {
    raw_to_celsius_CalledCount++;
    raw_to_celsius_RawArg_actual = raw;
    return raw_to_celsius_Return;
}

// --- setUp and tearDown functions ---
void setUp(void) {
    // Reset stub state
    raw_to_celsius_CalledCount = 0;
    raw_to_celsius_Return = 0.0f;
    raw_to_celsius_RawArg_actual = 0;

    // Seed rand() for somewhat repeatable (but still random) results for read_temperature_raw
    // Note: For truly deterministic testing of rand(), a more advanced mocking framework
    // or linker-level interposition would be needed. Here, we mostly check range.
    srand(0); // Using a fixed seed for consistency across test runs for read_temperature_raw
}

void tearDown(void) {
    // Reset stub state again to ensure isolation (critical requirement)
    raw_to_celsius_CalledCount = 0;
    raw_to_celsius_Return = 0.0f;
    raw_to_celsius_RawArg_actual = 0;
}

// --- Test Cases for read_temperature_raw ---
void TEST_read_temperature_raw_returns_value_in_expected_range(void) {
    int val1 = read_temperature_raw();
    TEST_ASSERT_TRUE(val1 >= 0 && val1 <= 1023);

    int val2 = read_temperature_raw();
    TEST_ASSERT_TRUE(val2 >= 0 && val2 <= 1023);

    int val3 = read_temperature_raw();
    TEST_ASSERT_TRUE(val3 >= 0 && val3 <= 1023);
}

// --- Test Cases for validate_temperature_range ---
void TEST_validate_temperature_range_valid_min_boundary(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f));
}

void TEST_validate_temperature_range_valid_max_boundary(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f));
}

void TEST_validate_temperature_range_valid_mid_range(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
}

void TEST_validate_temperature_range_invalid_too_low(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-40.1f));
}

void TEST_validate_temperature_range_invalid_too_high(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.1f));
}

void TEST_validate_temperature_range_valid_just_above_min(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(-39.99f));
}

void TEST_validate_temperature_range_valid_just_below_max(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(124.99f));
}

// --- Test Cases for check_temperature_status ---
void TEST_check_temperature_status_critical_high(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.01f));
}

void TEST_check_temperature_status_critical_edge(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(150.0f));
}

void TEST_check_temperature_status_hot_high(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.01f));
}

void TEST_check_temperature_status_hot_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f));
}

void TEST_check_temperature_status_cold_low(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-10.01f));
}

void TEST_check_temperature_status_cold_edge(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-40.0f));
}

void TEST_check_temperature_status_normal_mid(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
}

void TEST_check_temperature_status_normal_low_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-10.0f));
}

void TEST_check_temperature_status_normal_high_boundary(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f));
}

// --- Test Cases for get_temperature_celsius ---
void TEST_get_temperature_celsius_returns_converted_value_from_stub(void) {
    raw_to_celsius_Return = 50.5f;

    float result = get_temperature_celsius();

    // Verify raw_to_celsius was called once
    TEST_ASSERT_EQUAL(1, raw_to_celsius_CalledCount);

    // Verify the return value matches the stub's configured return
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 50.5f, result);

    // Verify the argument passed to raw_to_celsius was within the expected range (0-1023)
    TEST_ASSERT_TRUE(raw_to_celsius_RawArg_actual >= 0 && raw_to_celsius_RawArg_actual <= 1023);
}

void TEST_get_temperature_celsius_different_stub_value(void) {
    raw_to_celsius_Return = -5.75f;

    float result = get_temperature_celsius();

    TEST_ASSERT_EQUAL(1, raw_to_celsius_CalledCount);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -5.75f, result);
    TEST_ASSERT_TRUE(raw_to_celsius_RawArg_actual >= 0 && raw_to_celsius_RawArg_actual <= 1023);
}

// --- Main function to run tests ---
