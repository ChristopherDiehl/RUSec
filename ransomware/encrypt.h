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


/*
 * arg1 = filename 
 * arg2 = key
 * arg3 = iv
*/
int encrypt(int argc, char ** argv);

const unsigned BUFFSIZE=4096;
