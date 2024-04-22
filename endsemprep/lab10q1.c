#include <stdio.h>
#include<stdlib.h>

int FIFO(int *pages, int npages, int nframes)
{
	int *frames = (int*)calloc(nframes,(sizeof(int)));
	int paegFaults = 0;
	int nextFrameIndex = 0;
	
	for(int i=0; i<npages;i++)
	{
		int page = pages[i];
		int pageFound =0;
		
		for(int j =0; j<nframes;j++)
		{
			if(page == frames[j])
			{
				pageFound =1;
				break;
			}
		}
		
		if(!pageFound)
		{
			frames[nextFrameIndex] = page;
			nextFrameIndex = (nextFrameIndex +1)%nframes;
			paegFaults++;
		}
		
		
	}
	
	return paegFaults;
	
}

int main()
{
	int np,nf;
	
	printf("Enter number of pages: ");
	scanf("%d",&np);
	
	printf("Enter number of frames: ");
	scanf("%d",&nf);
	
	int *pages = (int *)malloc(np * sizeof(int));
	
	printf("Enter page reference sequence: ");
	for (int i = 0; i < np; i++) {
        scanf("%d", &pages[i]);
    }
    
    	    int fifoFaults = FIFO(pages, np, nf);
    	    
    	     printf("Page faults using FIFO algorithm: %d\n", fifoFaults );
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
