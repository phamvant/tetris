CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = main.c canvas.c
OBJS = $(SRCS:.c=.o)
HEADERS = canvas.h

TARGET = tetris

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
