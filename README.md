# Temperature Sensor C Project

A clean C development repository for temperature sensor functionality with converter utilities.

## Project Structure

```
├── src/
│   ├── main.c              # Main application entry point
│   ├── temp_sensor.c       # Temperature sensor implementation
│   ├── temp_sensor.h       # Temperature sensor header
│   ├── temp_converter.c    # Temperature conversion utilities
│   └── temp_converter.h    # Temperature converter header
├── CMakeLists.txt          # CMake build configuration
├── Makefile               # GNU Make build configuration
└── README.md             # This file
```

## Features

- **Temperature Sensor**: Core temperature reading functionality
- **Temperature Converter**: Convert between Celsius and Fahrenheit
- **Cross-platform**: Builds on Linux, macOS, and Windows
- **Multiple build systems**: CMake and GNU Make support

## Building

### Using CMake (Recommended)
```bash
mkdir build
cd build
cmake ..
make
./temperature_sensor
```

### Using Make
```bash
make
./temperature_sensor
```

## Development

This repository contains only the core source code for development. All test-related files and AI test generation tools have been removed to maintain a clean development environment.

## Functions

- `float raw_to_celsius(int raw_value)` - Convert raw ADC value to Celsius
- `float celsius_to_fahrenheit(float temp_c)` - Convert Celsius to Fahrenheit
- `bool is_temperature_rising(float prev_temp, float current_temp, float threshold)` - Check if temperature is rising
- `float get_temperature_celsius(void)` - Get current temperature reading
# Test trigger
