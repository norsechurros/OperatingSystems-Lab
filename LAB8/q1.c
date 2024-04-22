#include <stdio.h>

// Number of processes
#define P 5

// Number of resources
#define R 3

// Function to find the need of each process
void calculateNeed(int need[P][R], int max[P][R], int allocation[P][R])
{
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

// Function to check if the system is in a safe state
int isSafe(int processes[], int available[], int max[][R], int allocation[][R])
{
    int need[P][R];
    calculateNeed(need, max, allocation);

    int finish[P] = {0};
    int safeSeq[P];
    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = available[i];

    int count = 0;
    while (count < P)
    {
        int found = 0;
        for (int p = 0; p < P; p++)
        {
            if (finish[p] == 0)
            {
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R)
                {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            printf("System is not in safe state\n");
            return 0;
        }
    }

    printf("System is in safe state.\nSafe sequence is: ");
    for (int i = 0; i < P - 1; i++)
        printf("P%d -> ", safeSeq[i]);
    printf("P%d\n", safeSeq[P - 1]);
    return 1;
}

// Function to allocate resources to a process
void resourceRequest(int processes[], int request[], int available[], int max[][R], int allocation[][R])
{
    int need[P][R];
    calculateNeed(need, max, allocation);

    for (int i = 0; i < R; i++)
    {
        if (request[i] > need[processes[0]][i])
        {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
        if (request[i] > available[i])
        {
            printf("Error: Insufficient resources available.\n");
            return;
        }
    }

    for (int i = 0; i < R; i++)
    {
        allocation[processes[0]][i] += request[i];
        available[i] -= request[i];
    }

    if (isSafe(processes, available, max, allocation))
        printf("Resources allocated.\n");
    else
    {
        printf("Resources not allocated. Reverting changes.\n");
        for (int i = 0; i < R; i++)
        {
            allocation[processes[0]][i] -= request[i];
            available[i] += request[i];
        }
    }
}

int main()
{
    int processes[] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int available[] = {3, 3, 2};

    // Maximum R that can be allocated to processes
    int max[P][R] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {2, 2, 2},
                     {4, 3, 3}};

    // Resources allocated to processes
    int allocation[P][R] = {{0, 1, 0},
                            {2, 0, 0},
                            {3, 0, 2},
                            {2, 1, 1},
                            {0, 0, 2}};

    // Request made by processes
    int request[R] = {0, 2, 0};

    printf("Initial State:\n");
    printf("Available resources: ");
    for (int i = 0; i < R; i++)
        printf("%d ", available[i]);
    printf("\n");

    printf("Maximum resources:\n");
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }

    printf("Resources allocated:\n");
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
            printf("%d ", allocation[i][j]);
        printf("\n");
    }

    printf("\n");

    // Check if the system is in a safe state
    isSafe(processes, available, max, allocation);

    printf("\n");

    // Request resources by a process
    resourceRequest(processes, request, available, max, allocation);

    return 0;
}

/* ./q1 
Initial State:
Available resources: 3 3 2 
Maximum resources:
7 5 3 
3 2 2 
9 0 2 
2 2 2 
4 3 3 
Resources allocated:
0 1 0 
2 0 0 
3 0 2 
2 1 1 
0 0 2 

System is in safe state.
Safe sequence is: P1 -> P3 -> P4 -> P0 -> P2

System is in safe state.
Safe sequence is: P3 -> P1 -> P2 -> P0 -> P4
Resources allocated.
*/
