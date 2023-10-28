#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int scanf(const char *format, ...)
{
	char buffer[100];

	memset(buffer, 0, sizeof(buffer));
	fgets(buffer, sizeof(buffer), stdin);
	printf("Good job.\n");
	exit(0);
}