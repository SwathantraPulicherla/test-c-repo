#include "temp_converter.h"

float raw_to_celsius(int raw_value) {
    return (raw_value / 1023.0) * 165.0 - 40.0;
}

float celsius_to_fahrenheit(float temp_c) {
    return (temp_c * 9.0 / 5.0) + 32.0;
}

bool is_temperature_rising(float prev_temp, float current_temp, float threshold) {
    return (current_temp - prev_temp) > threshold;
}