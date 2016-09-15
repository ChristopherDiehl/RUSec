CC = gcc
CFLAGS = -g -Wall -o
DEPS = encrypt.c fileRecursor.c curlHelper.c
OBJECTS =encrypt.o curlHelper.o fileRecursor.o
EXECS = driver

all:
	$(CC) -c encrypt.c
	$(CC) -c fileRecursor.c
	$(CC) -c curlHelper.c -lcurl


	$(CC) $(CFLAGS) driver driver.c $(OBJECTS) -lcrypto -lcurl


clean:
	rm *.o $(EXECS)