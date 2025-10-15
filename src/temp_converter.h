#ifndef TEMP_CONVERTER_H
#define TEMP_CONVERTER_H

#include <stdbool.h>

float raw_to_celsius(int raw_value);
float celsius_to_fahrenheit(float temp_c);
bool is_temperature_rising(float prev_temp, float current_temp, float threshold);

#endif // TEMP_CONVERTER_H