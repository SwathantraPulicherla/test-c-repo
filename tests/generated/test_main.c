#include "unity.h"
#include "temp_sensor.h"
#include "temp_converter.h"

// ====================================================================
// Stub Implementations for functions that need stubs
// ====================================================================

static float get_temperature_celsius_Return;
static int get_temperature_celsius_CallCount;

float get_temperature_celsius() {
    get_temperature_celsius_CallCount++;
    return get_temperature_celsius_Return;
}

// ====================================================================
// SetUp / TearDown functions for Unity
// ====================================================================

void setUp(void) {
    // Reset stub states before each test
    get_temperature_celsius_Return = 0.0f;
    get_temperature_celsius_CallCount = 0;
}

void tearDown(void) {
    // No specific cleanup needed after each test for this module
}

// ====================================================================
// Tests for temp_converter.h functions
// (These are the functions 'main' from src/main.c would use,
// and are the testable units according to the "Test functions individually,
// not main() or complex workflows" rule, while providing necessary stubs.)
// ====================================================================

void test_check_temperature_status_cold(void) {
    TEST_ASSERT_EQUAL_STRING("Cold", check_temperature_status(0.0f));
    TEST_ASSERT_EQUAL_STRING("Cold", check_temperature_status(-10.0f));
    TEST_ASSERT_EQUAL_STRING("Cold", check_temperature_status(9.99f)); // Just below 10.0, still cold
}

void test_check_temperature_status_normal(void) {
    TEST_ASSERT_EQUAL_STRING("Normal", check_temperature_status(10.0f)); // Lower boundary for normal
    TEST_ASSERT_EQUAL_STRING("Normal", check_temperature_status(20.0f));
    TEST_ASSERT_EQUAL_STRING("Normal", check_temperature_status(29.99f)); // Just below 30.0, still normal
}

void test_check_temperature_status_hot(void) {
    TEST_ASSERT_EQUAL_STRING("Hot", check_temperature_status(30.0f)); // Lower boundary for hot
    TEST_ASSERT_EQUAL_STRING("Hot", check_temperature_status(35.0f));
    TEST_ASSERT_EQUAL_STRING("Hot", check_temperature_status(45.5f)); // High temperature
}

// ====================================================================
// Main function to run all tests
// ====================================================================

