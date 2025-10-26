#include "unity.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "temp_sensor.h"

extern int main(void);

// === STUB for get_temperature_celsius ===
static int get_temperature_celsius_CalledCount;
static float get_temperature_celsius_Returns;

void stub_get_temperature_celsius_reset(void) {
    get_temperature_celsius_CalledCount = 0;
    get_temperature_celsius_Returns = 0.0f;
}

float get_temperature_celsius(void) {
    get_temperature_celsius_CalledCount++;
    return get_temperature_celsius_Returns;
}

void expect_get_temperature_celsius_returns(float value) {
    get_temperature_celsius_Returns = value;
}
// =========================================

// === Standard Output Redirection Utilities ===
static int original_stdout_fd;
static char stdout_buffer[512];
static const char* STDOUT_FILE = "stdout.tmp";

void redirect_stdout(void) {
    fflush(stdout);
    original_stdout_fd = dup(fileno(stdout));
    freopen(STDOUT_FILE, "w+", stdout);
}

void restore_stdout(void) {
    fflush(stdout);
    fclose(stdout);
    dup2(original_stdout_fd, fileno(stdout));
    close(original_stdout_fd);

    FILE* temp_file = fopen(STDOUT_FILE, "r");
    if (temp_file) {
        memset(stdout_buffer, 0, sizeof(stdout_buffer));
        fread(stdout_buffer, 1, sizeof(stdout_buffer) - 1, temp_file);
        fclose(temp_file);
        remove(STDOUT_FILE);
    } else {
        strcpy(stdout_buffer, "ERROR: Could not open stdout.tmp for reading.");
    }
}
// =============================================

// === setUp and tearDown functions ===
void setUp(void) {
    stub_get_temperature_celsius_reset();
}

void tearDown(void) {
    // No specific cleanup needed here.
}

// === Test Cases for main() ===

void test_main_normal_temperature(void) {
    expect_get_temperature_celsius_returns(25.5f);
    redirect_stdout();
    int result = main();
    restore_stdout();

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_CalledCount);
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Temperature: 25.50 C"));
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Status: Normal"));
}

void test_main_low_temperature(void) {
    expect_get_temperature_celsius_returns(5.0f);
    redirect_stdout();
    int result = main();
    restore_stdout();

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_CalledCount);
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Temperature: 5.00 C"));
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Status: Cold"));
}

void test_main_high_temperature(void) {
    expect_get_temperature_celsius_returns(70.0f);
    redirect_stdout();
    int result = main();
    restore_stdout();

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_CalledCount);
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Temperature: 70.00 C"));
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Status: Hot"));
}

void test_main_edge_temperature_zero(void) {
    expect_get_temperature_celsius_returns(0.0f);
    redirect_stdout();
    int result = main();
    restore_stdout();

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_CalledCount);
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Temperature: 0.00 C"));
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Status: Cold"));
}

void test_main_edge_temperature_threshold_low_boundary_normal(void) {
    expect_get_temperature_celsius_returns(10.1f);
    redirect_stdout();
    int result = main();
    restore_stdout();

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_CalledCount);
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Temperature: 10.10 C"));
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Status: Normal"));
}

void test_main_edge_temperature_threshold_low_boundary_cold(void) {
    expect_get_temperature_celsius_returns(10.0f);
    redirect_stdout();
    int result = main();
    restore_stdout();

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_CalledCount);
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Temperature: 10.00 C"));
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Status: Cold"));
}

void test_main_edge_temperature_threshold_high_boundary_normal(void) {
    expect_get_temperature_celsius_returns(59.9f);
    redirect_stdout();
    int result = main();
    restore_stdout();

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_CalledCount);
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Temperature: 59.90 C"));
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Status: Normal"));
}

void test_main_edge_temperature_threshold_high_boundary_hot(void) {
    expect_get_temperature_celsius_returns(60.0f);
    redirect_stdout();
    int result = main();
    restore_stdout();

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(1, get_temperature_celsius_CalledCount);
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Temperature: 60.00 C"));
    TEST_ASSERT_NOT_NULL(strstr(stdout_buffer, "Status: Hot"));
}

// === Main Test Runner ===
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_main_normal_temperature);
    RUN_TEST(test_main_low_temperature);
    RUN_TEST(test_main_high_temperature);
    RUN_TEST(test_main_edge_temperature_zero);
    RUN_TEST(test_main_edge_temperature_threshold_low_boundary_normal);
    RUN_TEST(test_main_edge_temperature_threshold_low_boundary_cold);
    RUN_TEST(test_main_edge_temperature_threshold_high_boundary_normal);
    RUN_TEST(test_main_edge_temperature_threshold_high_boundary_hot);
    return UNITY_END();
}