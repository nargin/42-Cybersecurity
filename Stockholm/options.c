#include "stockholm.h"

void	version(void)
{
	printf("Stockholm version %s\n", STOCKHOLM_VERSION);
}

void	help(void)
{
	printf("%s", HELP);
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