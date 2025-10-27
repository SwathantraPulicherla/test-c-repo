#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h" // For stubbed function signature
#include <string.h> // For string comparison (TEST_ASSERT_EQUAL_STRING)
#include <stdlib.h> // Required for rand() if not already included by temp_sensor.h

// --- STUB FUNCTIONS ---
static int raw_to_celsius_Calls;
static float raw_to_celsius_Return;

float raw_to_celsius(int raw_value) {
    raw_to_celsius_Calls++;
    (void)raw_value; // Suppress unused parameter warning
    return raw_to_celsius_Return;
}

// --- UNITY SETUP AND TEARDOWN ---
void setUp(void) {
    // Reset stub state
    raw_to_celsius_Calls = 0;
    raw_to_celsius_Return = 0.0f;
}

void tearDown(void) {
    // Reset stub state (redundant but good practice for ensuring isolation)
    raw_to_celsius_Calls = 0;
    raw_to_celsius_Return = 0.0f;
}

// --- TEST FUNCTIONS ---

// Test read_temperature_raw
void test_read_temperature_raw_returns_within_range(void) {
    int raw_value = read_temperature_raw();
    TEST_ASSERT_TRUE_MESSAGE(raw_value >= 0, "read_temperature_raw should return non-negative value");
    TEST_ASSERT_TRUE_MESSAGE(raw_value < 1024, "read_temperature_raw should return value less than 1024");
}

// Test validate_temperature_range
void test_validate_temperature_range_valid(void) {
    TEST_ASSERT_TRUE(validate_temperature_range(0.0f));
    TEST_ASSERT_TRUE(validate_temperature_range(25.0f));
    TEST_ASSERT_TRUE(validate_temperature_range(-40.0f)); // Edge case: min
    TEST_ASSERT_TRUE(validate_temperature_range(125.0f)); // Edge case: max
}

void test_validate_temperature_range_invalid_low(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(-40.01f));
    TEST_ASSERT_FALSE(validate_temperature_range(-50.0f));
}

void test_validate_temperature_range_invalid_high(void) {
    TEST_ASSERT_FALSE(validate_temperature_range(125.01f));
    TEST_ASSERT_FALSE(validate_temperature_range(130.0f));
}

// Test check_temperature_status
void test_check_temperature_status_critical(void) {
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(120.01f));
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(125.0f)); // Max valid temp
    TEST_ASSERT_EQUAL_STRING("CRITICAL", check_temperature_status(150.0f));
}

void test_check_temperature_status_hot(void) {
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(85.01f));
    TEST_ASSERT_EQUAL_STRING("HOT", check_temperature_status(120.0f)); // Edge case
}

void test_check_temperature_status_cold(void) {
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-10.01f));
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-40.0f)); // Min valid temp
    TEST_ASSERT_EQUAL_STRING("COLD", check_temperature_status(-50.0f));
}

void test_check_temperature_status_normal(void) {
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(-10.0f)); // Edge case
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(0.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(25.0f));
    TEST_ASSERT_EQUAL_STRING("NORMAL", check_temperature_status(85.0f)); // Edge case
}

// Test get_temperature_celsius
void test_get_temperature_celsius_calls_converter(void) {
    raw_to_celsius_Return = 25.5f;
    float temp_c = get_temperature_celsius();
    TEST_ASSERT_EQUAL(1, raw_to_celsius_Calls);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 25.5f, temp_c);
}

void test_get_temperature_celsius_different_raw_conversion(void) {
    raw_to_celsius_Return = -5.0f;
    float temp_c = get_temperature_celsius();
    TEST_ASSERT_EQUAL(1, raw_to_celsius_Calls);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, -5.0f, temp_c);
}

void test_get_temperature_celsius_zero_conversion(void) {
    raw_to_celsius_Return = 0.0f;
    float temp_c = get_temperature_celsius();
    TEST_ASSERT_EQUAL(1, raw_to_celsius_Calls);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.0f, temp_c);
}

// --- MAIN TEST RUNNER ---
