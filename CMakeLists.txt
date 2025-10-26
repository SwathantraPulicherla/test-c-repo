cmake_minimum_required(VERSION 3.10)
project(CTestGen)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Add coverage flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# Include directories
include_directories(unity/src)
include_directories(src)

# Find all source files in src directory
file(GLOB SRC_FILES "src/*.c")

# Create main library from source files
add_library(ctestgen_lib STATIC ${SRC_FILES})

# Create main executable
add_executable(main_app src/main.c)
target_link_libraries(main_app ctestgen_lib)

# Find all generated test files
file(GLOB GENERATED_TESTS "${CMAKE_SOURCE_DIR}/tests/generated/*_test.c")
message(STATUS "Found generated test files: ${GENERATED_TESTS}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

# Create test executables for each generated test
foreach(TEST_FILE ${GENERATED_TESTS})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    message(STATUS "Creating test executable: ${TEST_NAME} from ${TEST_FILE}")
    add_executable(${TEST_NAME} ${TEST_FILE} unity/src/unity.c)
    target_link_libraries(${TEST_NAME} ctestgen_lib)
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

    # Add test to CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Custom target to regenerate CMake when test files change
add_custom_target(regenerate_tests
    COMMAND ${CMAKE_COMMAND} -E echo "Regenerating tests..."
    COMMAND python ${CMAKE_SOURCE_DIR}/../src/scripts/run_testgen.py ${CMAKE_SOURCE_DIR} --build
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Regenerating and rebuilding tests"
)

# Enable testing
enable_testing()

# Coverage target using lcov (if available)
find_program(LCOV lcov)
find_program(GENHTML genhtml)

if(LCOV AND GENHTML AND NOT WIN32)
    # Create coverage directory
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/coverage-report)

    # Coverage target
    add_custom_target(coverage
        # Clean previous coverage data
        COMMAND ${LCOV} --directory . --zerocounters

        # Run all test executables dynamically
        COMMAND ${CMAKE_COMMAND} -E echo "Running test executables..."
        COMMAND sh -c "for exe in test_*; do [ -x \"$exe\" ] && echo \"Running $exe...\" && ./$exe; done || true"

        # Capture coverage data
        COMMAND ${LCOV} --directory . --capture --output-file coverage.info

        # Filter out test files and external libraries
        COMMAND ${LCOV} --remove coverage.info '*/unity/*' '*/tests/*' '*/build/*' --output-file coverage_filtered.info

        # Generate HTML report
        COMMAND ${GENHTML} coverage_filtered.info --output-directory ../coverage-report

        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage report..."
    )
else()
    if(WIN32)
        message(STATUS "Coverage reporting disabled on Windows (lcov compatibility issues)")
    else()
        message(WARNING "lcov or genhtml not found. Coverage reporting will not be available.")
    endif()

    # Dummy coverage target for Windows
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E echo "Coverage reporting not available on this platform"
        COMMAND ${CMAKE_COMMAND} -E echo "Test executables are available in the build directory"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Coverage reporting not supported on this platform"
    )
endif()

# Clean coverage files
add_custom_target(clean_coverage
    COMMAND ${CMAKE_COMMAND} -E remove -f *.gcda *.gcno coverage.info coverage_filtered.info
    COMMAND ${CMAKE_COMMAND} -E remove_directory coverage-report
    COMMENT "Cleaning coverage files..."
)