#include <stdio.h>
#include <stdlib.h> // Include this header for exit() function

#define P 5
#define R 3 // Fixed to match the number of resources

void calculateNeed(int need[P][R], int allocation[P][R], int max[P][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void isSafe(int processes[], int available[], int max[][R], int allocation[][R]) {
    int need[P][R];
    calculateNeed(need, allocation, max); // Changed the order of parameters

    int finish[P] = {0};
    int safeSeq[P];
    int work[R];

    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int count = 0;

    while (count < P) {
        int found = 0;
        for (int p = 0; p < P; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j])
                        break;
                }

                if (j == R) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            printf("System is not in a safe state\n");
            exit(0); // Terminating the program
        }
    }

    printf("System is in a safe state\n");
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};
    int available[] = {3, 3, 2};
    int max[P][R] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    int allocation[P][R] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

    printf("Initial State:\n");
    printf("Available resources: ");
    for (int i = 0; i < R; i++)
        printf("%d ", available[i]);
    printf("\n");

    printf("Maximum resources:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }

    printf("Resources allocated:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++)
            printf("%d ", allocation[i][j]);
        printf("\n");
    }

    printf("\n");

    isSafe(processes, available, max, allocation);

    printf("\n");

    return 0;
}

