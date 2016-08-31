#ifndef ENCRYPT_H
#define ENCRYPT_H



#endif

#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdio.h>


/* Preproccessor statements*/
size_t get_file_length(char * filename);
int encrypt (char * filename, unsigned char * key, unsigned char * iv);
int decrypt(char * filename, unsigned char * key, unsigned char * iv);
char * concat(char * filename);
char * deconcat(char * filename);

#define BUFFSIZE 4096

//key needs to be 256, iv needs to be 128