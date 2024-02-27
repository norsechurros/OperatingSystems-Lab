#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> // Include the sys/wait.h header for wait()
#include <unistd.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

// Function to compare strings for qsort
int compare_strings(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string1> <string2> ... <stringN>\n", argv[0]);
        return 1;
    }

    int num_strings = argc - 1;
    char strings[MAX_STRINGS][MAX_LENGTH];

    // Copy command-line arguments into strings array
    for (int i = 0; i < num_strings; i++) {
        strncpy(strings[i], argv[i + 1], MAX_LENGTH);
    }

    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process:\n");
        printf("Sorted strings:\n");
        // Sort the strings
        qsort(strings, num_strings, MAX_LENGTH, compare_strings);
        // Display sorted strings
        for (int i = 0; i < num_strings; i++) {
            printf("%s\n", strings[i]);
        }
    } else {
        // Parent process
        // Wait for child to finish
        wait(NULL);
        printf("Parent process:\n");
        printf("Unsorted strings:\n");
        // Display unsorted strings
        for (int i = 0; i < num_strings; i++) {
            printf("%s\n", argv[i + 1]);
        }
    }

    return 0;
}
