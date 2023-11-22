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

struct cryptFile	readKey(void)
{
	struct cryptFile	data;
	memset(data.key, 0, sizeof(data.key));
	memset(data.nonce, 0, sizeof(data.nonce));
	// use fseek to get the size of the file
	FILE	*fp = fopen("key.crypt", "rb");
	if (fp == NULL)
	{
		printf("Error: fopen() failed\n");
		exit(1);
	}
	int		flen = filelen("key.crypt");
	if (flen == -1)
	{
		printf("Error: key.cript not found that can cause troubles... :x\n");
		exit(1);
	}
	char	*buffer = malloc(flen + 1);

	fread(buffer, sizeof(char), flen, fp);
	buffer[flen] = 0;
	fclose(fp);

	printf("%s\n\n", buffer);
	int		i = 6;
	char	*occ = strstr(buffer, "nonce");
	int		occ_index = occ - buffer;
	int 	j = 0;
	while (i < occ_index - 1 && buffer[i] != '\n')
		data.key[j++] = buffer[i++];
	data.key[j] = 0;
	i += 9;
	j = 0;
	while (i < flen - 1)
		data.nonce[j++] = buffer[i++];
	data.nonce[j] = 0;
	free(buffer);
	return (data);
}

void	decrypt(struct linkedFile *list)
{
	(void)list;
	struct cryptFile	data = readKey();
	printf("key : %s\n", data.key);
	printf("nonce : %s\n", data.nonce);
	newext(&list);

	// for (struct linkedFile *tmp = list; tmp; tmp = tmp->next)
	// 	printf("name : %s\n", tmp->file);
	
	if (TEST)
		chdir("crypted");
	// while (list)
	// {
	// 	char	*file = list->file;
	// 	int		file_size = filelen(file);
	// 	char	*buffer = malloc(file_size * sizeof(char));
	// 	if (!buffer)
	// 		exit(1);
	// 	FILE	*fp = fopen(file, "rb");
	// 	if (fp == NULL)
	// 	{
	// 		printf("Error: fopen() failed\n");
	// 		return ;
	// 	}
	// 	fread(buffer, sizeof(char), file_size, fp);
	// 	fclose(fp);
	// 	buffer[file_size] = 0;
	// 	unsigned char	*decrypted = malloc(file_size * sizeof(char));
	// 	if (!decrypted)
	// 		exit(1);


	// 	list = list->next;		
	// }
}