#include <stdio.h>
#include "encrypt.h"
#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdio.h>

int decrypt(char * filename, unsigned char * key, unsigned char * iv)
{
	size_t file_length = get_file_length(filename)+1;
	FILE * encrypted_file = fopen(filename,"rb");
	int out1 = 0; int out2 = 0;
	unsigned char * encrypted_file_buffer = malloc(file_length);
	unsigned char * decrypted_file_buffer = malloc(file_length- BUFFSIZE);


	EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();
	if ( 1 != EVP_DecryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv))
		exit(-1);
	EVP_DecryptUpdate(ctx,decrypted_file_buffer,&out1,encrypted_file_buffer,file_length);
	EVP_DecryptFinal(ctx,decrypted_file_buffer+out1,&out2);

	if(encrypted_file == 0)
		exit(-1);

	fread(encrypted_file_buffer,1,file_length,encrypted_file);
	fclose(encrypted_file);
	remove(filename);

	FILE * decrypted_file = fopen(filename,"w");
	fwrite(decrypted_file_buffer,1,out1+out2,decrypted_file);
	fclose(decrypted_file);

	free(encrypted_file_buffer);
	free(decrypted_file_buffer);

	return 1;
}

int main (int argc, char ** argv) 
{
	if (argc != 2)
	{
		printf("[-] pass in file");
	}

	unsigned char * key = (unsigned char *)"01234567890123456789012345678901";

	unsigned char *iv = (unsigned char *)"01234567890123456";

	printf("[-] Encrypting Now\n");
	//encrypt("file_to_encrypt.txt",key,iv);
	printf("[-] Encryption finished\n");

	decrypt("file_to_encrypt.txt",key,iv);
	printf("Decryption finished");
	return 1;
}