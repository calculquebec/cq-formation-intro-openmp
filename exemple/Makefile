CC=gcc

SRCS=$(wildcard *.c)

OBJS=$(SRCS:.c=.out)

all: $(OBJS)

%.out: %.c
	$(CC) -fopenmp -o $@ $<  -lm

