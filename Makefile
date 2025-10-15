CC = gcc
CFLAGS = -Isrc -Iunity -Wall -Wextra
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage

SRCS = src/temp_sensor.c src/temp_converter.c src/main.c
OBJS = $(SRCS:.c=.o)
TARGET = temp_app

TEST_SRCS = tests/generated/test_temp_sensor.c tests/generated/test_main.c unity/unity.c src/temp_sensor.c src/temp_converter.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_TARGET = test_runner

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -o $@ $(TEST_OBJS)

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

unity/%.o: unity/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET) *.gcda *.gcno *.info coverage_report -r
