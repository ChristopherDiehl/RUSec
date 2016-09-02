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
//key needs to be 256, iv needs to be 128

size_t get_file_length(char * filename);
int encrypt (char * filename, unsigned char * key, unsigned char * iv);
int decrypt(char * filename, unsigned char * key, unsigned char * iv);
char * concat(char * filename);
char * deconcat(char * filename);

#define BUFFSIZE 4096



/*
char * concat(char * filename)
{
	char * return_val = malloc(strlen(filename) +2);
	strcpy(return_val,filename);
	strcpy(return_val,"c");
	return return_val;
}

char * deconcat(char * filename)
{
	filename[strlen(filename)-1] = '\0';
	return filename;
}
*/