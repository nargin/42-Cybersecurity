#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

const char base32_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

char    *base32_encode(const char *input) {
    size_t  input_len = strlen(input);
    size_t  output_len = ((input_len * 8) + 4) / 5;
    size_t  padding_len = (8 - (output_len % 8)) % 8;
    size_t  total_len = output_len + padding_len;

    char    *output = malloc(total_len + 1);
    if (output == NULL) {
        return NULL;
    }

    for (size_t i = 0, j = 0; i < input_len;) {
        uint32_t octet_a = i < input_len ? (unsigned char)input[i++] : 0;
        uint32_t octet_b = i < input_len ? (unsigned char)input[i++] : 0;
        uint32_t octet_c = i < input_len ? (unsigned char)input[i++] : 0;
        uint32_t octet_d = i < input_len ? (unsigned char)input[i++] : 0;
        uint32_t octet_e = i < input_len ? (unsigned char)input[i++] : 0;

        uint32_t concat = (octet_a << 20) | (octet_b << 15) | (octet_c << 10) | (octet_d << 5) | octet_e;

        for (int k = 6; k >= 0; k--) {
            output[j++] = base32_alphabet[(concat >> k * 5) & 0x1F];
        }
    }

    for (size_t i = 0; i < padding_len; i++) {
        printf("padding\n");
        output[output_len + i] = '='; // Add padding
    }

    output[total_len] = '\0';
    return output;
}

int main(int ac, char *av[]) {
    (void)ac;
    char *output = base32_encode(av[1]);
    if (output == NULL) {
        return 1;
    }

    printf("%s\n", output);
    free(output);
    abort();
    printf("done\n");
    return 0;
}