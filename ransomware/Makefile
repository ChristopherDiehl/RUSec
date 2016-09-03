CC = gcc
CFLAGS = -g -Wall -o
DEPS = encrypt.c simpleList.c
OBJECTS = encrypt.o simpleList.o
EXECS = driver

all:
	$(CC) -c encrypt.c
	$(CC) -c simpleList.c

	$(CC) $(CFLAGS) driver driver.c $(OBJECTS) -lcrypto
	$(CC) $(CFLAGS) server server.c $(OBJECTS) -lpthread


clean:
	rm *.o $(EXECS)