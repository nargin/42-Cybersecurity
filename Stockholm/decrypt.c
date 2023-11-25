#include "stockholm.h"

void	newext(struct linkedFile **list)
{
	struct linkedFile	*fnode = (*list);
	int	i;
	int	eof = 1; // \0
	int	ext = 3; // ".ft"

	while (*list)
	{
		i = 0;
		while ((*list)->file[i] && (*list)->file[i] != '.')
			i++;

		char *nx = malloc((i + ext + eof) * sizeof(char));
		
		i = -1;
		while ((*list)->file[++i] && (*list)->file[i] != '.')
			nx[i] = (*list)->file[i];
		nx[i++] = '.';
		nx[i++] = 'f';
		nx[i++] = 't';
		nx[i] = 0;

		memcpy((*list)->file, nx, strlen(nx) + eof);
		free(nx);
		
		(*list) = (*list)->next;
	}
	(*list) = fnode;
}

void	readKey(struct cryptFile *data)
{
	FILE	*fp = fopen("key.crypt", "rb");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: fopen() failed\n");
		exit(1);
	}
	
	(*data).key = malloc(crypto_secretbox_KEYBYTES + 1);
	(*data).nonce = malloc(crypto_secretbox_NONCEBYTES + 1);

	bzero((*data).key, crypto_secretbox_KEYBYTES + 1);
	bzero((*data).nonce, crypto_secretbox_NONCEBYTES + 1);

	if ((*data).key == NULL || (*data).nonce == NULL)
	{
		fprintf(stderr, "Allocation memory failed :<\n");
		exit(1);
	}

	for (unsigned int i = 0; i < crypto_secretbox_KEYBYTES; i++)
		(*data).key[i] = fgetc(fp);
	fclose(fp);

	fp = fopen("nonce.crypt", "rb");
	if (fp == NULL)
	{
		printf("Error: fopen() failed\n");
		return ;
	}
	for (unsigned int i = 0; i < crypto_secretbox_NONCEBYTES; i++)
		(*data).nonce[i] = fgetc(fp);
	fclose(fp);
}

void	decrypt(struct linkedFile *list)
{
	struct cryptFile	data;

	readKey(&data);
	newext(&list);

	printf("%s\n", data.key);
	printf("%s\n", data.nonce);

	// for (struct linkedFile *tmp = list; tmp; tmp = tmp->next)
	// 	printf("name : %s\n", tmp->file);
	
	if (TEST)
		chdir("crypted");
	list = list->next;

	while (list)
	{
		FILE *fp = fopen(list->file, "rb");
		if (fp == NULL)
		{
			fprintf(stderr, "%s can't be open !\n", list->file);
			exit(1);
		}
		
		fseek(fp, 0, SEEK_END);
		long	flen = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		printf("%ld\n", flen);

		unsigned char	decrypted[flen + 1];

		// if (crypto_secretbox_open_easy(decrypted, 
		// {
		// 	fprintf(stderr, "%s file : Decryption failed\n", list->file);
		// 	exit(1);
		// }
		if (silent == 0)
			printf("\033[1;35mFile %s is now decrypted !\033[0m\n", list->file);
		fp = fopen(list->file, "wb");
		if (fp == NULL)
		{
			fprintf(stderr, "%s can't be open !\n", list->file);
			exit(1);
		}
		fwrite(decrypted, sizeof(char), flen, fp);
		fclose(fp);
		list = list->next;
	}
}