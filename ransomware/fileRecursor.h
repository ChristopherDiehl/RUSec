#ifndef FILERECURSOR_H
#define FILERECURSOR_H

#include <errno.h>
#include <sys/dir.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "encrypt.h"


/*preprocessor*/
void directory_handle(char * name,unsigned char * iv, unsigned char * key);
void file_handler(char * filepath, char * filename,unsigned char * iv, unsigned char * key);
void startEncrypting(char * start,unsigned char * iv, unsigned char * key);


#endif

