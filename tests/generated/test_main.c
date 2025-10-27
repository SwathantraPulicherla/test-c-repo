#include "unity.h"
#include <stdio.h>    // For freopen, printf, FILE, etc.
#include <string.h>   // For strcmp, memset (implied by TEST_ASSERT_EQUAL_STRING)

// Headers from source
#include "temp_sensor.h"
#include "temp_converter.h"

// Declare main from src/main.c to allow calling it in tests.
// This assumes the build system renames or excludes the main function
// from src/main.c to avoid a duplicate symbol with the test runner's main.
extern int main(void);

// Stubs for functions that need stubs
static float get_temperature_celsius_ReturnValue;
static int get_temperature_celsius_CallCount;

float get_temperature_celsius() {
    get_temperature_celsius_CallCount++;
    return get_temperature_celsius_ReturnValue;
}

// Global variables for stdout redirection
static FILE *g_temp_output_file = NULL;
static const char *TEMP_OUTPUT_FILENAME = "test_output.txt";
static char g_output_buffer[512]; // Buffer to hold captured output

void setUp(void) {
    // Reset stub state
    get_temperature_celsius_CallCount = 0;
    get_temperature_celsius_ReturnValue = 0.0f;

    // Remove any leftover temporary file from previous runs
    remove(TEMP_OUTPUT_FILENAME);

    // Redirect stdout to a temporary file
    fflush(stdout); // Flush any pending output to original stdout
    g_temp_output_file = freopen(TEMP_OUTPUT_FILENAME, "w+", stdout); // Redirect stdout
    TEST_ASSERT_NOT_NULL_MESSAGE(g_temp_output_file, "Failed to redirect stdout for testing.");
    setbuf(stdout, NULL); // Disable buffering for redirected stdout
}

void tearDown(void) {
    // Restore stdout to a safe state (discard output)
    fflush(stdout); // Flush any pending output to the temporary file
    if (g_temp_output_file != NULL) {
        fclose(g_temp_output_file); // Close the temporary file
        g_temp_output_file = NULL; // Clear pointer
    }
    
    // Reassign stdout to /dev/null or NUL to ensure subsequent printfs from test runner
    // or other modules don't go to the now-closed file. This is platform specific.
    freopen("/dev/null", "w", stdout); 

    // Clean up the temporary output file
    remove(TEMP_OUTPUT_FILENAME);
}

// Helper function to get the captured output
char* get_captured_output() {
    fflush(stdout); // Ensure all data is written to the temp file
    if (g_temp_output_file) {
        fseek(g_temp_output_file, 0, SEEK_SET); // Rewind to start of file
        memset(g_output_buffer, 0, sizeof(g_output_buffer));
        size_t bytes_read = fread(g_output_buffer, 1, sizeof(g_output_buffer) - 1, g_temp_output_file);
        g_output_buffer[bytes_read] = '\0'; // Null-terminate
    }
    return g_output_buffer;
}

void test_main_normal_temperature_output(void) {
    get_temperature_celsius_ReturnValue = 25.5f; // Set a normal temperature

     // Call the main function from src/main.c

    char expected_output[100];
    // Assuming check_temperature_status for 25.5f returns "OK"
    schar *captured_output = get_captured_output();
    TEST_ASSERT_EQUAL_STRING(expected_output, captured_output);
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}

void test_main_low_temperature_output(void) {
    get_temperature_celsius_ReturnValue = 5.0f; // Set a low temperature

     // Call the main function from src/main.c

    char expected_output[100];
    // Assuming check_temperature_status for 5.0f returns "LOW"
    schar *captured_output = get_captured_output();
    TEST_ASSERT_EQUAL_STRING(expected_output, captured_output);
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}

void test_main_high_temperature_output(void) {
    get_temperature_celsius_ReturnValue = 85.0f; // Set a high temperature

     // Call the main function from src/main.c

    char expected_output[100];
    // Assuming check_temperature_status for 85.0f returns "HIGH"
    schar *captured_output = get_captured_output();
    TEST_ASSERT_EQUAL_STRING(expected_output, captured_output);
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}

void test_main_zero_temperature_output(void) {
    get_temperature_celsius_ReturnValue = 0.0f; // Set zero temperature

     // Call the main function from src/main.c

    char expected_output[100];
    // Assuming check_temperature_status for 0.0f returns "LOW"
    schar *captured_output = get_captured_output();
    TEST_ASSERT_EQUAL_STRING(expected_output, captured_output);
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}

void test_main_negative_temperature_output(void) {
    get_temperature_celsius_ReturnValue = -10.0f; // Set negative temperature

     // Call the main function from src/main.c

    char expected_output[100];
    // Assuming check_temperature_status for -10.0f returns "LOW"
    schar *captured_output = get_captured_output();
    TEST_ASSERT_EQUAL_STRING(expected_output, captured_output);
    TEST_ASSERT_EQUAL_INT(1, get_temperature_celsius_CallCount);
}

// The main function for the Unity test runner
