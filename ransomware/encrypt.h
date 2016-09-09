#ifndef ENCRYPT_H
#define ENCRYPT_H




#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdio.h>


/* Preproccessor statements*/
//key needs to be 256, iv needs to be 128

size_t get_file_length(char * filename);
int encrypt (char * filename, unsigned char * key, unsigned char * iv);
int decrypt(char * filename, unsigned char * key, unsigned char * iv);

#define BUFFSIZE 4096

#endif
