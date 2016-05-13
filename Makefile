CC=gcc
SOURCES=test.c heap.c
CFLAGS=-c -Wall -Werror
OBJ=$(SOURCES:%.c=%.o)
EXECUTABLE=heap_test

all: $(SOURCES) $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(EXECUTABLE): $(OBJ)
	$(CC) $(OBJ) -o $(EXECUTABLE)

clean:
	-rm -rf *.o $(EXECUTABLE)
