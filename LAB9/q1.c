#include <stdio.h>
#include <stdlib.h>

// Structure to represent a hole
struct Hole {
    int size;
    int allocated;
};

// Structure to represent a process
struct Process {
    int size;
    int allocated;
};

// Function to allocate processes using First Fit algorithm
void firstFit(struct Hole holes[], int nh, struct Process processes[], int np) {
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nh; j++) {
            if (holes[j].size >= processes[i].size && !holes[j].allocated) {
                holes[j].allocated = 1;
                processes[i].allocated = 1;
                printf("Process %d allocated to hole %d\n", i+1, j+1);
                holes[j].size -= processes[i].size;
                break;
            }
        }
        if (!processes[i].allocated) {
            printf("Process %d cannot be allocated\n", i+1);
        }
    }
}

// Function to allocate processes using Best Fit algorithm
void bestFit(struct Hole holes[], int nh, struct Process processes[], int np) {
    // Sort holes by size in ascending order
    for (int i = 0; i < nh - 1; i++) {
        for (int j = 0; j < nh - i - 1; j++) {
            if (holes[j].size > holes[j+1].size) {
                struct Hole temp = holes[j];
                holes[j] = holes[j+1];
                holes[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nh; j++) {
            if (holes[j].size >= processes[i].size && !holes[j].allocated) {
                holes[j].allocated = 1;
                processes[i].allocated = 1;
                printf("Process %d allocated to hole %d\n", i+1, j+1);
                holes[j].size -= processes[i].size;
                break;
            }
        }
        if (!processes[i].allocated) {
            printf("Process %d cannot be allocated\n", i+1);
        }
    }
}

int main() {
    int nh, np;

    // Get number of holes
    printf("Enter the number of holes: ");
    scanf("%d", &nh);

    // Allocate memory for holes
    struct Hole *holes = (struct Hole *)malloc(nh * sizeof(struct Hole));

    // Get size of each hole
    printf("Enter the size of each hole:\n");
    for (int i = 0; i < nh; i++) {
        printf("Hole %d: ", i+1);
        scanf("%d", &holes[i].size);
        holes[i].allocated = 0;
    }

    // Get number of processes
    printf("\nEnter the number of processes: ");
    scanf("%d", &np);

    // Allocate memory for processes
    struct Process *processes = (struct Process *)malloc(np * sizeof(struct Process));

    // Get memory requirements for each process
    printf("Enter the memory requirements for each process:\n");
    for (int i = 0; i < np; i++) {
        printf("Process %d: ", i+1);
        scanf("%d", &processes[i].size);
        processes[i].allocated = 0;
    }

    // First Fit Allocation
    printf("\nFirst Fit Allocation:\n");
    firstFit(holes, nh, processes, np);

    // Reset allocations
    for (int i = 0; i < nh; i++) {
        holes[i].allocated = 0;
    }
    for (int i = 0; i < np; i++) {
        processes[i].allocated = 0;
    }

    // Best Fit Allocation
    printf("\nBest Fit Allocation:\n");
    bestFit(holes, nh, processes, np);

    // Free allocated memory
    free(holes);
    free(processes);

    return 0;
}


/*
./q1 
Enter the number of holes: 3
Enter the size of each hole:
Hole 1: 50
Hole 2: 100
Hole 3: 200

Enter the number of processes: 4
Enter the memory requirements for each process:
Process 1: 70
Process 2: 120
Process 3: 60
Process 4: 150 

First Fit Allocation:
Process 1 allocated to hole 2
Process 2 allocated to hole 3
Process 3 cannot be allocated
Process 4 cannot be allocated

Best Fit Allocation:
Process 1 allocated to hole 3
Process 2 cannot be allocated
Process 3 cannot be allocated
Process 4 cannot be allocated

*/
