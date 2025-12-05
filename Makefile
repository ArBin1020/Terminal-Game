CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = game

SRCS = src/main.c \
       $(wildcard src/core/*.c) \
       $(wildcard src/games/*.c)

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run