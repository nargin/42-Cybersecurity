#include <stdio.h>

int	main(int ac, char *av[]) {
	float a = 1.1431391224375825e+27;

	puts((char *)&a);
	printf("%f\n", a);

	// printf("\"");
	// for (int i = 32; i < 128; i++)
	// 	printf("%c", (char)i);
	// printf("\"");
	
	// int i = 0;
	// for (int c = 32; c < 128; c++, i++)
	// 	printf("%d: \"%c\"\n", i, (char)c);

	if (ac != 2)
		return (0);
	for (char *tmp = av[1]; *tmp; tmp++) {
		int i = 0;
		for (char c = 32; c < 128; c++, i++) {
			if (c == *tmp) {
				printf("s[%d]+", i);
				break;
			}
		}
	}
	printf("\n");
	return (0);
}