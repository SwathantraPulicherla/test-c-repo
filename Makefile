CC = gcc
CFLAGS = -Isrc -Wall -Wextra

SRCS = src/temp_sensor.c src/temp_converter.c src/main.c
OBJS = $(SRCS:.c=.o)
TARGET = temperature_sensor

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
