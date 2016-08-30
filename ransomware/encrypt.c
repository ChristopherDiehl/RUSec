#include "encrypt.h"


/*
 * arg1 = filename 
 * arg2 = key
 * arg3 = iv
*/
int encrypt (char * filename, unsigned char * key, unsigned char * iv)
{
	if (argc != 4) {
		printf("[filename] [key] [iv]");
	}

	size_t file_length = get_file_length(filename) +1;
	FILE * read_file = fopen(filename,"r");
	FILE * encrypted_file = fopen(filename,"wb");

	const unsigned BUFFSIZE=4096;
	unsigned char * r_buffer = malloc(file_length);
	unsigned char * c_buffer = malloc(file_length + BUFFSIZE);
	int out1 = 0; int out2 = 0;

	unsigned blocksize;
	int out_len;
	int return_val;

	fread(r_buffer,1,file_length, read_file);
	fclose(read_file);
	remove(filename);
	
	//Set up encryption
	EVP_CIPHER_CTX ctx;
	EVP_EncryptInit(&ctx,EVP_aes_128_cbc(),ckey,iv);
	EVP_EncryptUpdate(&ctx,c_buffer,&outLen1,r_buffer,file_length);
	EVP_EncryptFinal(&ctx,c_buffer + outLen1,&outLen2);
	fwrite(c_buffer,sizeof(char),outLen1 + outLen2,encrypted_file);

	// Free memory

	free(c_buffer);
	free(r_buffer);





}


size_t get_file_length(char * filename)
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}