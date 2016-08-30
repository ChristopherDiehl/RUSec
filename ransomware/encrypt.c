#include "encrypt.h"

int encrypt (char * filename, unsigned char * key, unsigned char * iv)
{

	size_t file_length = get_file_length(filename) +1;
	FILE * plaintext_file = fopen(filename,"r");
	
	unsigned char * p_buffer = malloc(file_length);
	unsigned char * c_buffer = malloc(file_length + BUFFSIZE);
	int out1 = 0; int out2 = 0;

	if (plaintext_file == 0) {
		printf("[-] File not found \n");
		exit(-1);
	}

	//printf("key: %u iv: %u",*(unsigned int *)key,*(unsigned int *)iv);

	EVP_CIPHER_CTX ctx;
	if ( 1 != EVP_EncryptInit_ex(&ctx,EVP_aes_256_cbc(),NULL,key,iv))
		exit(-1);
	
	EVP_EncryptUpdate(&ctx,c_buffer,&out1,p_buffer,file_length);
	EVP_EncryptFinal(&ctx,c_buffer + out1,&out2);

	fread(p_buffer,1,file_length, plaintext_file);
	fclose(plaintext_file);
	remove(filename);


	FILE * encrypted_file = fopen(filename,"wb");
	fwrite(c_buffer,1,out1 + out2,encrypted_file);

	free(c_buffer);
	free(p_buffer);
	fclose(encrypted_file);

	return 1;

}

int decrypt(char * filename, unsigned char * key, unsigned char * iv)
{
	size_t file_length = get_file_length(filename)+1;
	FILE * encrypted_file = fopen(filename,"rb");
	int out1 = 0; int out2 = 0;
	unsigned char * encrypted_file_buffer = malloc(file_length);
	unsigned char * decrypted_file_buffer = malloc(file_length- BUFFSIZE);

	fread(encrypted_file_buffer,1,file_length,encrypted_file);
	fclose(encrypted_file);
	remove(filename);

	EVP_CIPHER_CTX ctx;
	EVP_DecryptInit_ex(&ctx,EVP_aes_256_cbc(),NULL,key,iv);
	EVP_DecryptUpdate(&ctx,decrypted_file_buffer,&out1,encrypted_file_buffer,file_length);
	EVP_DecryptFinal(&ctx,decrypted_file_buffer+out1,&out2);

	FILE * decrypted_file = fopen(filename,"w");
	fwrite(decrypted_file_buffer,1,out1+out2,decrypted_file);
	fclose(decrypted_file);

	free(encrypted_file_buffer);
	free(decrypted_file_buffer);

	return 1;
}

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

size_t get_file_length(char * filename)
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}