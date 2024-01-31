#include <stdio.h>
#include <stdint.h>
#include <string.h>

float binaryStringToFloat(const char *binaryString) {
	uint32_t binaryRepresentation = 0;
	size_t length = strlen(binaryString);

	// Convert binary string to integer
	for (size_t i = 0; i < length; ++i) {
		if (binaryString[i] == '1') {
			binaryRepresentation = (binaryRepresentation << 1) | 1;
		}
		else if (binaryString[i] == '0') {
			binaryRepresentation = binaryRepresentation << 1;
		}
		else if (binaryString[i] == ' ') {
			continue;
		}
		else {
			return 0.0f;
		}
	}

	float result;
	memcpy(&result, &binaryRepresentation, sizeof(float));
	return result;
}

void printBinary(float value) {
	uint32_t binaryRepresentation;
	memcpy(&binaryRepresentation, &value, sizeof(float));

	for (int i = 31; i >= 0; --i) {
		int bit = (binaryRepresentation >> i) & 1;
		printf("%d", bit);
		if (i % 4 == 0)
			printf(" ");
	}
	printf("\n");
}

int	main(int ac, char *av[]) {
	float arg133 = 203402367973537611776.000000;
	float arg123 = 1023031902208.000000;
	float arg132 = binaryStringToFloat("00110111011010010110111000110100");
	float arg122 = binaryStringToFloat("0010000101111001");
	float a[100] = {arg133, arg123, arg132, arg122};

	puts((char *)a);
	// if (ac == 1) {
	// 	printf("C float value: %.6f\n", c);	
	// }

	// if (ac == 2 && (*av[1] == '0' || *av[1] == '1')) {
		// c = binaryStringToFloat(av[1]);
		// printf("float format: %f\n", c);
		// printf("string format: ");
		// puts((char *)&c);
		// return (0);
	// }

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