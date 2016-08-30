#include "encrypt.h"


/*
 * arg1 = filename 
 * arg2 = key
 * arg3 = iv
*/
int encrypt (int argc, char ** argv)
{
	if (argc != 4) {
		printf("[filename] [key] [iv]");
	}

	char * filename = argv[1];
	size_t file_length = get_file_length(filename) +1;
	FILE * file = fopen(filename,"r");


	if(file == 0)
	{
		printf("[-] Invalid file name passed to encrypt: %s\n",filename);
		return 0;
	}

	char * buffer = calloc(1,file_length);

	fread(buffer,file_length -1,1,file);
	fclose(file);
	remove(filename);

	


}


size_t get_file_length(char * filename)
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}