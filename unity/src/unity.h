#ifndef UNITY_H
#define UNITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Basic Unity framework implementation for testing

#define TEST_ASSERT_TRUE(condition) \
    if (!(condition)) { \
        printf("FAIL: %s:%d - Expected true, got false\n", __FILE__, __LINE__); \
        exit(1); \
    }

#define TEST_ASSERT_FALSE(condition) \
    if (condition) { \
        printf("FAIL: %s:%d - Expected false, got true\n", __FILE__, __LINE__); \
        exit(1); \
    }

#define TEST_ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        printf("FAIL: %s:%d - Expected %d, got %d\n", __FILE__, __LINE__, (expected), (actual)); \
        exit(1); \
    }

#define TEST_ASSERT_EQUAL_INT(expected, actual) TEST_ASSERT_EQUAL(expected, actual)

#define TEST_ASSERT_EQUAL_FLOAT(expected, actual) \
    if (fabsf((expected) - (actual)) > 0.0001f) { \
        printf("FAIL: %s:%d - Expected %f, got %f\n", __FILE__, __LINE__, (expected), (actual)); \
        exit(1); \
    }

#define TEST_ASSERT_FLOAT_WITHIN(tolerance, expected, actual) \
    if (fabsf((expected) - (actual)) > (tolerance)) { \
        printf("FAIL: %s:%d - Expected %f +/- %f, got %f\n", __FILE__, __LINE__, (expected), (tolerance), (actual)); \
        exit(1); \
    }

#define TEST_ASSERT_GREATER_OR_EQUAL_INT(threshold, actual) \
    if ((actual) < (threshold)) { \
        printf("FAIL: %s:%d - Expected >= %d, got %d\n", __FILE__, __LINE__, (threshold), (actual)); \
        exit(1); \
    }

#define TEST_ASSERT_LESS_OR_EQUAL_INT(threshold, actual) \
    if ((actual) > (threshold)) { \
        printf("FAIL: %s:%d - Expected <= %d, got %d\n", __FILE__, __LINE__, (threshold), (actual)); \
        exit(1); \
    }

#define TEST_ASSERT_EQUAL_STRING(expected, actual) \
    if (strcmp((expected), (actual)) != 0) { \
        printf("FAIL: %s:%d - Expected \"%s\", got \"%s\"\n", __FILE__, __LINE__, (expected), (actual)); \
        exit(1); \
    }

#endif // UNITY_H