#include "stockholm.h"

void	version(void)
{
	printf("Stockholm version %s\n", STOCKHOLM_VERSION);
}

void	help(void)
{
	printf("%s", HELP);
}

void	optionprog(char *option)
{
	if (strcmp("-h", option) == 0 || strcmp("--help", option) == 0)
		help();
	
	else if (strcmp("-v", option) == 0 || strcmp("--version", option) == 0)
		version();
	
	else if (strcmp("-r", option) == 0 || strcmp("--reverse", option) == 0)
		reverse = 1;

	else if (strcmp("-s", option) == 0 || strcmp("--silent", option) == 0)
		silent = 1;

	else if (strcmp("-rs", option) == 0 || strcmp("-sr", option) == 0 || strcmp("--reverse-silent", option) == 0 || strcmp("--silent-reverse", option) == 0)
	{
		reverse = 1;
		silent = 1;
	}

	else
		printf("%s", DEFAULT_HELP);
}