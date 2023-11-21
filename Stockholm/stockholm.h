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
#define HELP "Usage : ./stockholm [OPTION]\n\
Options :\n\t\
-h, --help\t\tDisplay every option available\n\t\
-v, --version\t\tDisplay the version of the program\n\t\
-r, --reverse\t\tReverse every encrypted file \n"

struct linkedFile{
	char file[256];
	struct linkedFile *next;
};

void	version(void);
void	options(void);

#endif