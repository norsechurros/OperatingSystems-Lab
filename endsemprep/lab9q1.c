#include <stdio.h>
#include <stdlib.h>
typedef struct  
{
	int size;
	int allocated;
}Holes ;

typedef struct 
{
	int size;
	int allocated;
}Processes ;

void firstFit(Holes holes[],Processes processes[], int nh , int np)
{
	for(int i = 0; i< np; i++)
	{
		for(int j = 0;j<nh; j++)
		{
			if(holes[j].size > processes[i].size && !holes[j].allocated)
			{
				holes[j].allocated = 1;
				processes[i].allocated = 1;
				
				printf("process P%d allocated to hole H%d" ,i,j);
				
				holes[j].size -= processes[i].size;
				break;
				
			}
		}
	}
}

int main()
{int nh;
    printf("Enter number of holes: ");
    scanf("%d", &nh);
    
    Holes *holes = (Holes*)malloc(nh * sizeof(Holes));
    
    printf("Enter hole sizes: ");
    for (int i = 0; i < nh; i++) {
        scanf("%d", &holes[i].size);
        holes[i].allocated = 0;
    }
    
    int np;
    printf("\nEnter the number of processes: ");
    scanf("%d", &np);
    
    Processes *processes = (Processes*)malloc(np * sizeof(Processes));
    
    printf("Enter the memory requirements for each process:\n");
    for (int i = 0; i < np; i++) {
        printf("Process %d: ", i+1);
        scanf("%d", &processes[i].size);
        processes[i].allocated = 0;
    }
    
    printf("\nFirst Fit Allocation:\n");
    firstFit(holes, processes, nh, np);
	
}

