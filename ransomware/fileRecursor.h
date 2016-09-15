#ifndef FILERECURSOR_H
#define FILERECURSOR_H

#include <errno.h>
#include <sys/dir.h>

/*preprocessor*/
void directory_handle(char * name);
void file_handler(char * filepath, char * filename);
void delete_file_paths();

#endif

