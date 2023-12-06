CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -O2

# Program name
SRC=ex13q1.c
OUT=ex13q1

all: fastio easyio

fastio: $(SRC)
	@$(CC) $(CFLAGS) -DFASTIO -o $(OUT)_fastio $(SRC)

easyio: $(SRC)
	@$(CC) $(CFLAGS) -DEASYIO -o $(OUT)_easyio $(SRC)

clean:
	@rm -f $(OUT)_fastio $(OUT)_easyio
