
#include "unity.h"
#include "temp_converter.h" // Include the header for the functions under test
#include <stdbool.h>        // For bool type

// Define a delta for float comparisons to account for floating-point inaccuracies
#define FLOAT_DELTA 0.001f

// Setup function - called before each test
void setUp(void) {
    // No specific setup needed for these stateless functions
}

// Teardown function - called after each test
void tearDown(void) {
    // No specific teardown needed
}

// --- Tests for raw_to_celsius ---

void test_rawToCelsius_MinRawValue(void) {
    int raw_value = 0;
    float expected_celsius = -40.0f; // (0 / 1023.0f) * 165.0f - 40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, expected_celsius, actual_celsius);
}

void test_rawToCelsius_MaxRawValue(void) {
    int raw_value = 1023;
    float expected_celsius = 125.0f; // (1023 / 1023.0f) * 165.0f - 40.0f = 165.0f - 40.0f
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, expected_celsius, actual_celsius);
}

void test_rawToCelsius_MidRangeRawValue(void) {
    int raw_value = 511; // Approximately half of 1023
    float expected_celsius = (511.0f / 1023.0f) * 165.0f - 40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, expected_celsius, actual_celsius);
}

void test_rawToCelsius_SpecificRawValue(void) {
    int raw_value = 767;
    float expected_celsius = (767.0f / 1023.0f) * 165.0f - 40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, expected_celsius, actual_celsius);
}

void test_rawToCelsius_NegativeRawValue(void) {
    // Though raw_value typically implies positive sensor readings, testing negative input
    // checks the formula's mathematical behavior without assuming sensor constraints.
    int raw_value = -100;
    float expected_celsius = (-100.0f / 1023.0f) * 165.0f - 40.0f;
    float actual_celsius = raw_to_celsius(raw_value);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, expected_celsius, actual_celsius);
}

// --- Tests for celsius_to_fahrenheit ---

void test_celsiusToFahrenheit_FreezingPoint(void) {
    float temp_c = 0.0f;
    float expected_f = 32.0f;
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, expected_f, actual_f);
}

void test_celsiusToFahrenheit_BoilingPoint(void) {
    float temp_c = 100.0f;
    float expected_f = 212.0f; // (100.0f * 9.0f / 5.0f) + 32.0f = 180.0f + 32.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, expected_f, actual_f);
}

void test_celsiusToFahrenheit_NegativeCelsius(void) {
    float temp_c = -10.0f;
    float expected_f = 14.0f; // (-10.0f * 9.0f / 5.0f) + 32.0f = -18.0f + 32.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, expected_f, actual_f);
}

void test_celsiusToFahrenheit_RoomTemperature(void) {
    float temp_c = 25.0f;
    float expected_f = 77.0f; // (25.0f * 9.0f / 5.0f) + 32.0f = 45.0f + 32.0f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, expected_f, actual_f);
}

void test_celsiusToFahrenheit_ArbitraryValue(void) {
    float temp_c = 37.5f;
    float expected_f = (37.5f * 9.0f / 5.0f) + 32.0f; // 67.5f + 32.0f = 99.5f
    float actual_f = celsius_to_fahrenheit(temp_c);
    TEST_ASSERT_FLOAT_WITHIN(FLOAT_DELTA, expected_f, actual_f);
}

// --- Tests for is_temperature_rising ---

void test_isTemperatureRising_ClearlyRising(void) {
    float prev_temp = 20.0f;
    float current_temp = 22.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

void test_isTemperatureRising_BarelyRising(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.001f; // Just above threshold
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result);
}

void test_isTemperatureRising_ExactlyAtThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 21.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // (21.0f - 20.0f) > 1.0f is false (1.0f > 1.0f is false)
}

void test_isTemperatureRising_BelowThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result);
}

void test_isTemperatureRising_FallingTemperature(void) {
    float prev_temp = 22.0f;
    float current_temp = 20.0f;
    float threshold = 1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // (20.0f - 22.0f) = -2.0f, -2.0f > 1.0f is false
}

void test_isTemperatureRising_ZeroThreshold_Rising(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.001f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // (20.001f - 20.0f) = 0.001f, 0.001f > 0.0f is true
}

void test_isTemperatureRising_ZeroThreshold_NoChange(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.0f;
    float threshold = 0.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // (20.0f - 20.0f) = 0.0f, 0.0f > 0.0f is false
}

void test_isTemperatureRising_NegativeThreshold_RisingSlightly(void) {
    float prev_temp = 20.0f;
    float current_temp = 20.5f;
    float threshold = -1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // (20.5f - 20.0f) = 0.5f, 0.5f > -1.0f is true
}

void test_isTemperatureRising_NegativeThreshold_FallingSlightly(void) {
    float prev_temp = 20.0f;
    float current_temp = 19.5f;
    float threshold = -1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_TRUE(result); // (19.5f - 20.0f) = -0.5f, -0.5f > -1.0f is true
}

void test_isTemperatureRising_NegativeThreshold_FallingBelowThreshold(void) {
    float prev_temp = 20.0f;
    float current_temp = 18.0f;
    float threshold = -1.0f;
    bool result = is_temperature_rising(prev_temp, current_temp, threshold);
    TEST_ASSERT_FALSE(result); // (18.0f - 20.0f) = -2.0f, -2.0f > -1.0f is false
}


// Main function to run all tests
int main(void) {
    UNITY_BEGIN();

    // raw_to_celsius tests
    RUN_TEST(test_rawToCelsius_MinRawValue);
    RUN_TEST(test_rawToCelsius_MaxRawValue);
    RUN_TEST(test_rawToCelsius_MidRangeRawValue);
    RUN_TEST(test_rawToCelsius_SpecificRawValue);
    RUN_TEST(test_rawToCelsius_NegativeRawValue);

    // celsius_to_fahrenheit tests
    RUN_TEST(test_celsiusToFahrenheit_FreezingPoint);
    RUN_TEST(test_celsiusToFahrenheit_BoilingPoint);
    RUN_TEST(test_celsiusToFahrenheit_NegativeCelsius);
    RUN_TEST(test_celsiusToFahrenheit_RoomTemperature);
    RUN_TEST(test_celsiusToFahrenheit_ArbitraryValue);

    // is_temperature_rising tests
    RUN_TEST(test_isTemperatureRising_ClearlyRising);
    RUN_TEST(test_isTemperatureRising_BarelyRising);
    RUN_TEST(test_isTemperatureRising_ExactlyAtThreshold);
    RUN_TEST(test_isTemperatureRising_BelowThreshold);
    RUN_TEST(test_isTemperatureRising_FallingTemperature);
    RUN_TEST(test_isTemperatureRising_ZeroThreshold_Rising);
    RUN_TEST(test_isTemperatureRising_ZeroThreshold_NoChange);
    RUN_TEST(test_isTemperatureRising_NegativeThreshold_RisingSlightly);
    RUN_TEST(test_isTemperatureRising_NegativeThreshold_FallingSlightly);
    RUN_TEST(test_isTemperatureRising_NegativeThreshold_FallingBelowThreshold);


    return UNITY_END();
}
