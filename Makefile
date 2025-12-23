CC = gcc
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags libmodbus)
LDFLAGS = $(shell pkg-config --libs libmodbus)

SRC = main.c Pollutant.c DList.c
OUT = app

all:
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)
