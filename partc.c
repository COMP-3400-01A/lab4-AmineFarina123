#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    // we need exactly 2 arguments: the word to search for, and the file
    if (argc != 3) {
        printf("ERROR: No arguments\n");
        return 1;
    }

    char* word = argv[1];
    char* filename = argv[2];

    int pid = fork();

    if (pid == 0) {
        // we are the child, this is where we run grep
        char* eargs[6];
        eargs[0] = "grep";
        eargs[1] = "-s";
        eargs[2] = "-q";
        eargs[3] = word;
        eargs[4] = filename;
        eargs[5] = NULL;

        execv("/usr/bin/grep", eargs);

        // if we get here, execv must have failed
        printf("ERROR: exec failed\n");
        return 1;
    } else {
        // we are the parent, so we wait for the child to finish
        int status;
        wait(&status);

        int exitCode = WEXITSTATUS(status);

        if (exitCode == 0) {
            // grep found the word
            printf("FOUND: %s\n", word);
            return 0;
        } else if (exitCode == 1) {
            // grep ran fine but did not find the word
            printf("NOT FOUND: %s\n", word);
            return 0;
        } else {
            // anything else means something went wrong, like a missing file
            printf("ERROR: %s doesn't exist\n", filename);
            return 2;
        }
    }
}
