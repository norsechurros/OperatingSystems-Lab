#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUFLEN 10

int main(void) {
    char buffer[BUFLEN + 1]; // +1 for null terminator
    pid_t pid1;
    int i;

    pid1 = fork();

    if (pid1 == 0) {
        strncpy(buffer, "CHILD\n", BUFLEN);
        buffer[BUFLEN] = '\0'; // Null-terminate the string
    } else if (pid1 > 0) { // Parent process
        strncpy(buffer, "PARENT\n", BUFLEN);
        buffer[BUFLEN] = '\0'; // Null-terminate the string
    } else if (pid1 == -1) {
        printf("ERROR:\n");
        switch (errno) {
            case EAGAIN:
                printf("Cannot fork process: System Process Limit Reached\n");
                break;
            case ENOMEM:
                printf("Cannot fork process: Out of memory\n");
                break;
            default:
                printf("Unknown error in fork\n");
                break;
        }
        return 1;
    }

    for (i = 0; i < 5; ++i) {
        sleep(1);
        write(1, buffer, strlen(buffer));
    }

    return 0;
}
