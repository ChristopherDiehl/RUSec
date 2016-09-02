#include <stdio.h>
#include "encrypt.h"
int main (int argc, char ** argv) 
{
	if (argc != 2)
	{
		printf("[-] pass in file");
	}

	unsigned char * key = (unsigned char *)"01234567890123456789012345678901";

	unsigned char *iv = (unsigned char *)"01234567890123456";

	printf("[-] Encrypting Now\n");
	encrypt("file_to_encrypt.txt",key,iv);
	printf("[-] Encryption finished\n");

	//decrypt("[-]Decrypting Now\n");
	return 1;
}