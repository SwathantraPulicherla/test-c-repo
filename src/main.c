#include <stdio.h>
#include "temp_sensor.h"
#include "temp_converter.h"

int main() {
    float temp = get_temperature_celsius();
    printf("Temperature: %.2f C\n", temp);
    printf("Status: %s\n", check_temperature_status(temp));
    return 0;
}