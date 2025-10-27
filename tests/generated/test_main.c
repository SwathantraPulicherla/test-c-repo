#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"

// --- STUB IMPLEMENTATIONS ---

// Stub variables for get_temperature_celsius
static float stub_get_temperature_celsius_ret_val;
static int stub_get_temperature_celsius_call_count;

// Stub function for get_temperature_celsius
float get_temperature_celsius() {
    stub_get_temperature_celsius_call_count++;
    return stub_get_temperature_celsius_ret_val;
}

// --- SET UP AND TEAR DOWN ---

void setUp(void) {
    // Reset stub state for get_temperature_celsius
    stub_get_temperature_celsius_ret_val = 25.0f; // Default realistic temperature
    stub_get_temperature_celsius_call_count = 0;
}

void tearDown(void) {
    // Reset stub state after each test to ensure isolation
    stub_get_temperature_celsius_ret_val = 0.0f; // Reset to a distinct default
    stub_get_temperature_celsius_call_count = 0;
}

// --- TEST CASES ---

// Note: Direct testing of main() is problematic due to its reliance on printf and exit,
// which are not unit-testable with a basic Unity setup as per the given constraints.
// Instead, we will test the functions that main() uses, specifically check_temperature_status
// from temp_converter.h, as it represents a critical part of main's logic and can be tested independently.
// We also test the behavior of the stub for get_temperature_celsius.

void test_check_temperature_status_normal(void) {
    const char* status = check_temperature_status(22.5f); // Normal room temperature
    TEST_ASSERT_EQUAL_STRING("Normal", status);
}

void test_check_temperature_status_high_threshold(void) {
    // Assuming 'High' status starts at 35.0C
    const char* status = check_temperature_status(35.0f);
    TEST_ASSERT_EQUAL_STRING("High", status);
    status = check_temperature_status(34.99f); // Just below high
    TEST_ASSERT_EQUAL_STRING("Normal", status);
}

void test_check_temperature_status_low_threshold(void) {
    // Assuming 'Low' status starts at or below 5.0C
    const char* status = check_temperature_status(5.0f);
    TEST_ASSERT_EQUAL_STRING("Low", status);
    status = check_temperature_status(5.01f); // Just above low
    TEST_ASSERT_EQUAL_STRING("Normal", status);
}

void test_check_temperature_status_extreme_high(void) {
    const char* status = check_temperature_status(50.0f); // Very high
    TEST_ASSERT_EQUAL_STRING("High", status);
}

void test_check_temperature_status_extreme_low(void) {
    const char* status = check_temperature_status(-10.0f); // Very low
    TEST_ASSERT_EQUAL_STRING("Low", status);
}

void test_check_temperature_status_at_zero(void) {
    const char* status = check_temperature_status(0.0f);
    TEST_ASSERT_EQUAL_STRING("Low", status); // Assuming 0C is considered 'Low'
}

void test_get_temperature_celsius_stub_returns_configured_value(void) {
    // Configure stub to return a specific value
    stub_get_temperature_celsius_ret_val = 15.5f;
    
    // Call the function that uses the stub
    float temp = get_temperature_celsius();
    
    // Assert the return value and call count
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 15.5f, temp);
    TEST_ASSERT_EQUAL(1, stub_get_temperature_celsius_call_count);
}

void test_get_temperature_celsius_stub_tracks_multiple_calls(void) {
    stub_get_temperature_celsius_ret_val = 20.0f;
    get_temperature_celsius(); // First call
    TEST_ASSERT_EQUAL(1, stub_get_temperature_celsius_call_count);

    stub_get_temperature_celsius_ret_val = 30.0f;
    get_temperature_celsius(); // Second call
    TEST_ASSERT_EQUAL(2, stub_get_temperature_celsius_call_count);
    
    // Verify the last returned value matches the last configured value
    float temp = get_temperature_celsius(); // Third call
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 30.0f, temp);
    TEST_ASSERT_EQUAL(3, stub_get_temperature_celsius_call_count);
}


// --- MAIN TEST RUNNER ---

