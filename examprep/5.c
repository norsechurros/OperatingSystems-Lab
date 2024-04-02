#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 10

struct Process 
{int id;
int arrival_time;
int burst_time;
int priority;
int remaining_time;
};

void sjf(struct Process processes[], int n)
{
int current_time = 0;
int completed = 0;
int shortest_job_index = -1;
int time_quant = 3;



while(completed < n)
{
shortest_job_index = -1;
int shortest_burst_time = __INT_MAX__;

for(int i =0;i<n;i++)
{
if(processes[i].arrival_time <= current_time && processes[i].remaining_time < shortest_burst_time && processes[i].remaining_time>0)
{
shortest_burst_time = processes[i].remaining_time;
shortest_job_index = i;
}
}

printf( "process %d is executing at time %d \n", processes[shortest_job_index].id,current_time);
processes[shortest_job_index].remaining_time --;

if(processes[shortest_job_index].remaining_time == 0){completed ++;}

current_time++;
}
}

void rr(struct Process processes[], int n, int time_quant )
{
int completed = 0;
int current_time = 0;

while ( completed<n ){
for(int i =0;i<n;i++){
if(processes[i].arrival_time<= current_time && processes[i].remaining_time>0)
{
printf("process %d is executing at %d \n", processes[i].id, current_time);

if(processes[i].remaining_time > time_quant)
{
current_time += time_quant;
processes[i].remaining_time -= time_quant;
}
else
{
current_time += processes[i].remaining_time;
processes[i].remaining_time = 0;
completed ++;

}
}
}
}
}


int main()
{
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
            sjf(processes, n);
            break;
        case 2:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &time_quantum);
            rr(processes, n, time_quantum);
            break;
    /*    case 3:
            priority_scheduling(processes, n);
            break;*/
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
