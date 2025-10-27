#include "temp_sensor.h"
#include "temp_converter.h"
#include <stdlib.h>

int read_temperature_raw() {
    return rand() % 1024;
}

bool validate_temperature_range(float temp_c) {
    return temp_c >= -40.0f && temp_c <= 125.0f;
}

const char* check_temperature_status(float temp_c) {
    if (temp_c > 120.0f) {
        return "CRITICAL";
    } else if (temp_c > 85.0f) {
        return "HOT";
    } else if (temp_c < -10.0f) {
        return "COLD";
    } else {
        return "NORMAL";
    }
}

float get_temperature_celsius() {
    int raw = read_temperature_raw();
    return raw_to_celsius(raw);
}