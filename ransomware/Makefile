CC = gcc
CFLAGS = -g -Wall -o
DEPS = encrypt.c
OBJECTS = encrypt.o 
EXECS = driver

all:
	$(CC) -c encrypt.c

	$(CC) $(CFLAGS) driver driver.c $(OBJECTS) -lcrypto

clean:
	rm *.o $(EXECS)