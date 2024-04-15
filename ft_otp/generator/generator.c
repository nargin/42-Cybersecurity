#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

const char HEX_CHAR[] = "0123456789ABCDEF";
enum OutputDisplay {
	FILE_FD, // Conflict with FILE macro
	CONSOLE
};

char *generate_key(int size) {
	char *key = malloc(size * sizeof(char) + 1);
	srand(time(NULL) ^ (getpid() << 16)); // Seed with time and pid
	for (int i = 0; i < size; i++) {
		key[i] = HEX_CHAR[rand() % 16]; 
	}
	key[size] = 0;
	return key;
}

int	file_output(int size) {
	FILE *file = fopen("hex.key", "w");

	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	
	const char *key = generate_key(size);

	fprintf(file, "%s", key);
	fclose(file);
	return 0;
}

int	console_output(int size) {
	const char *key = generate_key(size);
	printf("%s\n", key);
	return 0;
}

void	argument_parser(int ac, char *av[], int *size, enum OutputDisplay *display) {
	if (ac > 4) {
		printf("Too many arguments\n");
		exit(1);
	}
	for (int i = 1; i < ac; i++) {
		if (av[i][0] == '-') {
			switch (av[i][1]) {
				case 'h':
					printf("Usage: %s [-f file output] [-n size (default: 64)]\n", av[0]);
					exit(0);
				case 'n':
					if (i + 1 >= ac) {
						*size = 64;
						break;
					}
					*size = atoi(av[++i]);
					break;
				case 'f':
					*display = FILE_FD;
					break;
				default:
					printf("Invalid argument\n");
					exit(1);
			}
		}
	}
}

int	main(int ac, char *av[]) {
	int size = 64;
	enum OutputDisplay display = CONSOLE;

	argument_parser(ac, av, &size, &display);
	if (size <= 0) {
		printf("Putting back size to 64 characters\n");
		size = 64;
	}
	if (display == FILE_FD) {
		file_output(size);
	} else {
		console_output(size);
	}
}