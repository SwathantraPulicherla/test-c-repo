#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <stdbool.h>

int read_temperature_raw();
bool validate_temperature_range(float temp_c);
const char* check_temperature_status(float temp_c);
float get_temperature_celsius();

#endif // TEMP_SENSOR_H