#include <stdio.h>
#include <stdlib.h>

// Function to simulate FIFO page replacement algorithm
int simulateFIFO(int *pages, int nPages, int nFrames) {
    int *frames = (int *)calloc(nFrames, sizeof(int)); // Initialize frames with 0s to indicate empty frame
    int pageFaults = 0;
    int nextFrameIndex = 0;

    for (int i = 0; i < nPages; i++) {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page already exists in the frames
        for (int j = 0; j < nFrames; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        // If page not found, perform page replacement
        if (!pageFound) {
            frames[nextFrameIndex] = page;
            nextFrameIndex = (nextFrameIndex + 1) % nFrames; // Move to the next frame in a circular manner
            pageFaults++;
        }
    }

    free(frames);
    return pageFaults;
}

// Function to simulate Optimal page replacement algorithm
int simulateOptimal(int *pages, int nPages, int nFrames) {
    int *frames = (int *)calloc(nFrames, sizeof(int)); // Initialize frames with 0s to indicate empty frame
    int pageFaults = 0;

    for (int i = 0; i < nPages; i++) {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page already exists in the frames
        for (int j = 0; j < nFrames; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        // If page not found, perform page replacement
        if (!pageFound) {
            // Find the index of the frame to replace
            int replaceIndex = -1;
            int farthestIndex = i; // Initialize farthest index to current index

            for (int j = 0; j < nFrames; j++) {
                int nextPageIndex = i + 1;
                while (nextPageIndex < nPages && pages[nextPageIndex] != frames[j]) {
                    nextPageIndex++;
                }
                if (nextPageIndex > farthestIndex) {
                    farthestIndex = nextPageIndex;
                    replaceIndex = j;
                }
            }

            // Replace the page at replaceIndex
            frames[replaceIndex] = page;
            pageFaults++;
        }
    }

    free(frames);
    return pageFaults;
}

int main() {
    int nFrames, nPages;

    printf("Enter the number of frames: ");
    scanf("%d", &nFrames);

    printf("Enter the number of pages: ");
    scanf("%d", &nPages);

    int *pages = (int *)malloc(nPages * sizeof(int));

    printf("Enter the sequence of page references: ");
    for (int i = 0; i < nPages; i++) {
        scanf("%d", &pages[i]);
    }

    int fifoFaults = simulateFIFO(pages, nPages, nFrames);
    int optimalFaults = simulateOptimal(pages, nPages, nFrames);

    printf("Page faults using FIFO algorithm: %d\n", fifoFaults);
    printf("Page faults using Optimal algorithm: %d\n", optimalFaults);

    free(pages);
    return 0;
}

