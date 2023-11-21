#include "stockholm.h"

int	reverse = 0;

void	encrypt(struct linkedFile *list, struct cryptFile data)
{
	(void)list;
	(void)data;
	// if (crypto_secretbox_open_easy(decrypted, cypher, sizeof(cypher), nonce, key) != 0) {
	// 	printf("Decryption failed\n");
	// 	return 1;
	// }
	// printf("decrypt : %s\n", decrypted);
}

void	decrypt(struct linkedFile *list)
{
	(void)list;
	// unsigned char cypher[strlen(buffer) + crypto_secretbox_MACBYTES];

	// if (crypto_secretbox_easy(cypher, (const unsigned char *)"World", 5, data.nonce, data.key) != 0) {
	// 	printf("Encryption failed\n");
	// 	return 1;
	// }
	// printf("crypt : %s\n", cypher);
}

void	writeKey(struct cryptFile *data)
{
	unsigned int key_size = crypto_secretbox_KEYBYTES;  
	unsigned char key[key_size];
	unsigned char nonce[crypto_secretbox_NONCEBYTES];
	randombytes_buf(nonce, sizeof(nonce));
	crypto_secretbox_keygen(key);

	strcpy((*data).key, (char *)key);
	strcpy((*data).nonce, (char *)nonce); 

	FILE *fp = fopen("key.cript", "wb");

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
	{
		if ((reverse = optionprog(argv[1], argc)))
			goto init;
		return (0);
	}

	struct cryptFile data;
	writeKey(&data); // write key encrypt in key.cript "."
	printf("%s\n", FILE_DELETED);

	init:
	struct linkedFile *file = openFile();
	
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