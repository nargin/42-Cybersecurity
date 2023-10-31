#include "stockholm.h"

void	version(void)
{
	printf("Stockholm version %s\n", STOCKHOLM_VERSION);
}

int		main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	(void)env;
	if (sodium_init() == -1)
	{
		printf("Error: sodium_init() failed\n");
		return (1);
	}
	size_t key_size = crypto_secretbox_KEYBYTES;
	unsigned char key[key_size];
	randombytes_buf(key, key_size);

	FILE *fp = fopen("key.cript", "wb");

	if (fp == NULL)
	{
		printf("Error: fopen() failed\n");
		return (1);
	}
	fwrite(key, sizeof(unsigned char), key_size, fp);
	return (0);
}