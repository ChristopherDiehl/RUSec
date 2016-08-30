#include "encrypt.h"

int encrypt (char * filename, unsigned char * key, unsigned char * iv)
{

	size_t file_length = get_file_length(filename);
	FILE * plaintext_file = fopen(filename,"r");
	
	unsigned char * p_buffer = malloc(file_length);
	unsigned char * c_buffer = malloc(file_length + BUFFSIZE);
	int out1 = 0; int out2 = 0;

	if (plaintext_file == 0) {
		printf("[-] File not found \n");
		return -1;
	}

	fread(p_buffer,1,file_length, plaintext_file);
	fclose(plaintext_file);
	remove(filename);

	printf("%s",p_buffer);

	EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();

	if ( !EVP_EncryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv))
		return -1;

	EVP_EncryptUpdate(ctx,c_buffer,&out1,p_buffer,file_length);
	EVP_EncryptFinal(ctx,c_buffer + out1,&out2);
	EVP_CIPHER_CTX_cleanup(ctx);

	FILE * encrypted_file = fopen(filename,"wb");
	fwrite(c_buffer,1,out1+out2,encrypted_file);
	fclose(encrypted_file);

	free(c_buffer);
	free(p_buffer);

	return 1;

}

int decrypt(char * filename, unsigned char * key, unsigned char * iv)
{
	size_t file_length = get_file_length(filename);
	FILE * encrypted_file = fopen(filename,"rb");
	int out1 = 0; int out2 = 0;
	unsigned char * encrypted_file_buffer = calloc(1,file_length+1);
	unsigned char * decrypted_file_buffer = calloc(1,file_length+1);

	if(encrypted_file == 0)
		return -1;

	fread(encrypted_file_buffer,1,file_length,encrypted_file);
	fclose(encrypted_file);
	remove(filename);
	
	FILE * decrypted_file = fopen(filename,"w");

	EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();
	if ( !EVP_DecryptInit_ex(ctx,EVP_aes_256_cbc(),NULL,key,iv))
		exit(-1);
    EVP_DecryptUpdate(ctx,decrypted_file_buffer,&out1,encrypted_file_buffer,file_length);
    EVP_DecryptFinal(ctx,decrypted_file_buffer + out1,&out2);

    fwrite(decrypted_file_buffer,sizeof(char),out1 + out2,decrypted_file);

	fclose(decrypted_file);

	free(encrypted_file_buffer);
	free(decrypted_file_buffer);

	return 1;
}


size_t get_file_length(char * filename)
{
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}
