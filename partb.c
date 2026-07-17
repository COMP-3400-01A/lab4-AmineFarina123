#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // no arguments means we need to error out
    if (argc < 2) {
        char* msg = "ERROR: No arguments\n";
        write(1, msg, strlen(msg));
        return 1;
    }

    int numArgs = argc - 1; // how many real arguments the user gave us

    // this array holds the arguments we pass to exec
    // { "echo", middleArg1, middleArg2, NULL }
    char* eargs[4];
    eargs[0] = "echo";

    if (numArgs % 2 == 1) {
        // odd amount of arguments, so there is only one middle one
        int mid = argc / 2;
        eargs[1] = argv[mid];
        eargs[2] = NULL;
    } else {
        // even amount of arguments, so there are two middle ones
        int first = numArgs / 2;
        int second = first + 1;
        eargs[1] = argv[first];
        eargs[2] = argv[second];
        eargs[3] = NULL;
    }

    int result = execv("/bin/echo", eargs);

    // if execv worked, we never actually get here
    if (result == -1) {
        char* msg = "ERROR: exec failed\n";
        write(1, msg, strlen(msg));
        return 1;
    }

    return 0;
}
