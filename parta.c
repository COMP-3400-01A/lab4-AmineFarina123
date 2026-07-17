#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    // if the user didn't type any arguments, print an error
    if (argc < 2) {
        printf("ERROR: No arguments\n");
        return 1;
    }

    // loop through each argument they gave us
    for (int i = 1; i < argc; i++) {
        // put a comma before every argument except the first one
        if (i != 1) {
            printf(",");
        }

        // go letter by letter and make it uppercase
        for (int j = 0; argv[i][j] != '\0'; j++) {
            char letter = argv[i][j];
            printf("%c", toupper(letter));
        }
    }

    printf("\n");

    return 0;
}
