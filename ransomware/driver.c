#include <stdio.h>
#include "encrypt.h"
#include <openssl/evp.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdio.h>
#include <openssl/aes.h>

int main (int argc, char ** argv) 
{
	if (argc != 2)
	{
		printf("[-] pass in file");
	}

	unsigned char * key = (unsigned char *)"01234567890123456789012345678901";

	unsigned char *iv = (unsigned char *)"01234567890123456";

	printf("[-] Encrypting Now\n");
	encrypt("plaintext.txt",key,iv);
	printf("[-] Encryption finished\n");

	//decrypt("plaintext.txt",key,iv);
	printf("Decryption finished\n");
	return 1;
}

