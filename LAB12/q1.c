#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

// Task structure
typedef struct {
    int id;            // Task ID
    int period;        // Period of the task
    int execution_time;// Execution time of the task
    int deadline;      // Absolute deadline of the task
} Task;

// Function prototypes
void rate_monotonic(Task tasks[], int num_tasks, int simulation_time);
void earliest_deadline_first(Task tasks[], int num_tasks, int simulation_time);

int main() {
    // Define tasks
    Task tasks[MAX_TASKS] = {
        {1, 5, 1, 5},
        {2, 10, 2, 10},
        {3, 20, 3, 20}
    };

    int num_tasks = 3;
    int simulation_time = 50;

    printf("Rate-Monotonic Scheduling:\n");
    rate_monotonic(tasks, num_tasks, simulation_time);

    printf("\nEarliest-Deadline-First Scheduling:\n");
    earliest_deadline_first(tasks, num_tasks, simulation_time);

    return 0;
}

void rate_monotonic(Task tasks[], int num_tasks, int simulation_time) {
    int i, time;
    printf("Time\tTask\n");
    for (time = 0; time < simulation_time; time++) {
        int min_period_task = 0;
        for (i = 1; i < num_tasks; i++) {
            if (tasks[i].period < tasks[min_period_task].period)
                min_period_task = i;
        }
        if ((time % tasks[min_period_task].period) == 0)
            printf("%d\tTask %d\n", time, tasks[min_period_task].id);
    }
}

void earliest_deadline_first(Task tasks[], int num_tasks, int simulation_time) {
    int i, time;
    printf("Time\tTask\n");
    for (time = 0; time < simulation_time; time++) {
        int min_deadline_task = 0;
        for (i = 1; i < num_tasks; i++) {
            if (tasks[i].deadline < tasks[min_deadline_task].deadline)
                min_deadline_task = i;
        }
        if ((time % tasks[min_deadline_task].period) == 0)
            printf("%d\tTask %d\n", time, tasks[min_deadline_task].id);
    }
}
