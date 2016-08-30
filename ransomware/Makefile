CC = gcc
CFLAGS = -g -Wall -o
DEPS = encrypt.c SimpleList.c
OBJECTS = encrypt.o SimpleList.o
EXECS = driver

all:
	$(CC) -c encrypt.c
	$(CC) -c SimpleList.c

	$(CC) $(CFLAGS) driver driver.c $(OBJECTS) -lcrypto
	$(CC) $(CFLAGS) server server.c $(OBJECTS) -lpthread -lcrypto


clean:
	rm *.o $(EXECS)