#include <stdio.h>

#define MAX_TASKS 10

// Task structure
typedef struct {
    int period;     // Period of the task
    int deadline;   // Absolute deadline of the task
    int execution;  // Execution time of the task
    int remaining;  // Remaining execution time
} Task;

// Rate-Monotonic scheduling algorithm
void rateMonotonic(Task tasks[], int nTasks) {
    printf("Rate-Monotonic Scheduling\n");

    // Sort tasks by period (lower period implies higher priority)
    for (int i = 0; i < nTasks - 1; i++) {
        for (int j = i + 1; j < nTasks; j++) {
            if (tasks[j].period < tasks[i].period) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }

    // Simulate task execution
    int time = 0;
    while (time < 100) {  // Assuming simulation time is 100 units
        int executed = 0;
        for (int i = 0; i < nTasks; i++) {
            if (time % tasks[i].period == 0) {
                printf("Task %d executing\n", i + 1);
                executed = 1;
            }
        }
        if (!executed) {
            printf("Idle\n");
        }
        time++;
    }
}

// Earliest Deadline First scheduling algorithm
void earliestDeadlineFirst(Task tasks[], int nTasks) {
    printf("\nEarliest Deadline First Scheduling\n");

    // Sort tasks by deadline (earliest deadline has highest priority)
    for (int i = 0; i < nTasks - 1; i++) {
        for (int j = i + 1; j < nTasks; j++) {
            if (tasks[j].deadline < tasks[i].deadline) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }

    // Simulate task execution
    int time = 0;
    while (time < 100) {  // Assuming simulation time is 100 units
        int executed = 0;
        for (int i = 0; i < nTasks; i++) {
            if (tasks[i].remaining > 0 && time % tasks[i].period == 0) {
                printf("Task %d executing\n", i + 1);
                tasks[i].remaining -= 1;
                executed = 1;
            }
        }
        if (!executed) {
            printf("Idle\n");
        }
        time++;
    }
}

int main() {
    // Define tasks
    Task tasks[MAX_TASKS] = {
        {20, 20, 5, 5},  // Task 1: Period = 20, Deadline = 20, Execution time = 5
        {10, 10, 3, 3},  // Task 2: Period = 10, Deadline = 10, Execution time = 3
        {15, 15, 4, 4}   // Task 3: Period = 15, Deadline = 15, Execution time = 4
    };

    int nTasks = 3;  // Number of tasks

    // Perform Rate-Monotonic scheduling
    rateMonotonic(tasks, nTasks);

    // Perform Earliest Deadline First scheduling
    earliestDeadlineFirst(tasks, nTasks);

    return 0;
}

