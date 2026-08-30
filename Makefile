CC = gcc

CFLAGS = -Wall -Wextra -O3 -std=c99
LDFLAGS = -fopenmp -pthread

TARGET = mandelbrot

SRCS = mandelbrot.c calculo.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c calculo.h
	$(CC) $(CFLAGS) -fopenmp -pthread -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

