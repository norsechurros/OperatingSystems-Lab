#include <stdio.h>
#include <stdlib.h>

// Function to check if a page exists in frames
int pageExists(int page, int *frames, int nFrames) {
    for (int i = 0; i < nFrames; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

// Function to find the index of the page to be replaced using FIFO algorithm
int findReplacementIndexFIFO(int *frames, int nFrames, int currentIndex, int *pages, int nPages) {
    return (currentIndex + 1) % nFrames;
}

// Function to find the index of the page to be replaced using Optimal algorithm
int findReplacementIndexOptimal(int *frames, int nFrames, int currentIndex, int *pages, int nPages) {
    int farthestIndex = -1;
    int farthestDistance = -1;

    for (int i = 0; i < nFrames; i++) {
        int page = frames[i];
        int nextOccurrence = -1;

        for (int j = currentIndex + 1; j < nPages; j++) {
            if (pages[j] == page) {
                nextOccurrence = j;
                break;
            }
        }

        if (nextOccurrence == -1) {
            return i; // If a page will not be referenced again, replace it
        }

        if (nextOccurrence > farthestDistance) {
            farthestIndex = i;
            farthestDistance = nextOccurrence;
        }
    }

    return farthestIndex;
}

// Function to simulate page replacement algorithms
void simulatePageReplacement(int *pages, int nPages, int nFrames, int (*replacementFunction)(int*, int, int, int*, int), const char *algorithm) {
    int *frames = (int *)malloc(nFrames * sizeof(int));
    int pageFaults = 0;
    int currentIndex = 0;

    for (int i = 0; i < nFrames; i++) {
        frames[i] = -1; // Initialize frames with -1 to indicate empty frame
    }

    for (int i = 0; i < nPages; i++) {
        if (!pageExists(pages[i], frames, nFrames)) {
            int replacementIndex = replacementFunction(frames, nFrames, currentIndex, pages, nPages);
            frames[replacementIndex] = pages[i];
            currentIndex = (currentIndex + 1) % nFrames;
            pageFaults++;
        }
    }

    printf("Page faults using %s algorithm: %d\n", algorithm, pageFaults);
    free(frames);
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

    simulatePageReplacement(pages, nPages, nFrames, findReplacementIndexFIFO, "FIFO");
    simulatePageReplacement(pages, nPages, nFrames, findReplacementIndexOptimal, "Optimal");

    free(pages);
    return 0;
}

