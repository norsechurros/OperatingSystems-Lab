#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 10

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

// Function to perform preemptive Shortest Job First (SJF) scheduling
void preemptive_sjf(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int shortest_job_index;
    int time_quantum = 1;

    while (completed < n) {
        shortest_job_index = -1;
        int shortest_burst_time = __INT_MAX__;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < shortest_burst_time && processes[i].remaining_time > 0) {
                shortest_burst_time = processes[i].remaining_time;
                shortest_job_index = i;
            }
        }

        if (shortest_job_index == -1) {
            printf("Idle at time %d\n", current_time);
            current_time++;
        } else {
            printf("Process %d is executing at time %d\n", processes[shortest_job_index].id, current_time);
            processes[shortest_job_index].remaining_time--;

            if (processes[shortest_job_index].remaining_time == 0) {
                completed++;
            }

            current_time++;
        }
    }
}

// Function to perform Round Robin (RR) scheduling
void round_robin(struct Process processes[], int n, int time_quantum) {
    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                printf("Process %d is executing at time %d\n", processes[i].id, current_time);
                if (processes[i].remaining_time > time_quantum) {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    completed++;
                }
            }
        }
    }
}

// Function to perform non-preemptive Priority Scheduling
void priority_scheduling(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int highest_priority_index = -1;
        int highest_priority = __INT_MAX__;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }

        if (highest_priority_index == -1) {
            printf("Idle at time %d\n", current_time);
            current_time++;
        } else {
            printf("Process %d is executing at time %d\n", processes[highest_priority_index].id, current_time);
            current_time += processes[highest_priority_index].remaining_time;
            processes[highest_priority_index].remaining_time = 0;
            completed++;
        }
    }
}

int main() {
    int choice;
    int n;
    int time_quantum;
    struct Process processes[MAX_PROCESS];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].id = i + 1;
    }

    printf("Choose scheduling algorithm:\n");
    printf("1. Preemptive SJF\n");
    printf("2. Round Robin\n");
    printf("3. Non-preemptive Priority\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            preemptive_sjf(processes, n);
            break;
        case 2:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &time_quantum);
            round_robin(processes, n, time_quantum);
            break;
        case 3:
            priority_scheduling(processes, n);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}


/*./q1 
Enter the number of processes: 4
Enter arrival time for process 1: 0
Enter burst time for process 1: 8
Enter priority for process 1: 1
Enter arrival time for process 2: 5
Enter burst time for process 2: 4
Enter priority for process 2: 2
Enter arrival time for process 3: 3
Enter burst time for process 3: 9
Enter priority for process 3: 3
Enter arrival time for process 4: 7
Enter burst time for process 4: 16
Enter priority for process 4: 4
Choose scheduling algorithm:
1. Preemptive SJF
2. Round Robin
3. Non-preemptive Priority
Enter your choice: 2
Enter time quantum for Round Robin: 3
Process 1 is executing at time 0
Process 3 is executing at time 3
Process 1 is executing at time 6
Process 2 is executing at time 9
Process 3 is executing at time 12
Process 4 is executing at time 15
Process 1 is executing at time 18
Process 2 is executing at time 20
Process 3 is executing at time 21
Process 4 is executing at time 24
Process 4 is executing at time 27
Process 4 is executing at time 30
Process 4 is executing at time 33
Process 4 is executing at time 36
*/
