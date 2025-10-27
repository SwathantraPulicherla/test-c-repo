#include "temp_converter.h"

float raw_to_celsius(int raw_value) {
    return (raw_value / 1023.0f) * 165.0f - 40.0f;
}

float celsius_to_fahrenheit(float temp_c) {
    return (temp_c * 9.0f / 5.0f) + 32.0f;
}

bool is_temperature_rising(float prev_temp, float current_temp, float threshold) {
    return (current_temp - prev_temp) > threshold;
}