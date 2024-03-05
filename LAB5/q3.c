#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

// Function to swap two strings
void swap(char *a, char *b) {
    char temp[MAX_LENGTH];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

// Bubble sort
void bubble_sort(char strings[][MAX_LENGTH], int num_strings) {
    for (int i = 0; i < num_strings - 1; i++) {
        for (int j = 0; j < num_strings - i - 1; j++) {
            if (strcmp(strings[j], strings[j + 1]) > 0) {
                swap(strings[j], strings[j + 1]);
            }
        }
    }
}

// Selection sort
void selection_sort(char strings[][MAX_LENGTH], int num_strings) {
    int min_index;
    for (int i = 0; i < num_strings - 1; i++) {
        min_index = i;
        for (int j = i + 1; j < num_strings; j++) {
            if (strcmp(strings[j], strings[min_index]) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(strings[i], strings[min_index]);
        }
    }
}

int main() {
    int num_strings;
    char strings[MAX_STRINGS][MAX_LENGTH];

    // Read number of strings
    printf("Enter the number of strings: ");
    scanf("%d", &num_strings);
    getchar(); // Consume newline character

    // Read strings
    printf("Enter the strings:\n");
    for (int i = 0; i < num_strings; i++) {
        fgets(strings[i], MAX_LENGTH, stdin);
        // Remove newline character if present
        strings[i][strcspn(strings[i], "\n")] = '\0';
    }

    pid_t pid1, pid2;
    int status;

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        // Child process 1 (Bubble sort)
        bubble_sort(strings, num_strings);
        printf("Child process 1 (Bubble sort):\n");
        for (int i = 0; i < num_strings; i++) {
            printf("%s\n", strings[i]);
        }
        exit(0);
    } else {
        pid2 = fork();

        if (pid2 < 0) {
            perror("fork");
            exit(1);
        } else if (pid2 == 0) {
            // Child process 2 (Selection sort)
            selection_sort(strings, num_strings);
            printf("Child process 2 (Selection sort):\n");
            for (int i = 0; i < num_strings; i++) {
                printf("%s\n", strings[i]);
            }
            exit(0);
        } else {
            // Parent process
            // Wait for any child to terminate
            pid_t terminated_pid = wait(&status);
            if (terminated_pid == pid1) {
                printf("Child process 1 terminated.\n");
            } else if (terminated_pid == pid2) {
                printf("Child process 2 terminated.\n");
            }
            // Kill the other child process
            kill(pid1 == terminated_pid ? pid2 : pid1, SIGKILL);
        }
    }

    return 0;
}


/*./q3
Enter the number of strings: 3
Enter the strings:
hello
world
in
Child process 1 (Bubble sort):
hello
in
world
Child process 2 (Selection sort):
hello
in
world
Child process 1 terminated.
*/
