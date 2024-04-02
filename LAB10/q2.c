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

// Function to find the index of the least recently used page
int findLRUIndex(int *recentlyUsed, int nFrames) {
    int minIndex = 0;
    for (int i = 1; i < nFrames; i++) {
        if (recentlyUsed[i] < recentlyUsed[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to simulate LRU page replacement algorithm
void simulateLRUPageReplacement(int *pages, int nPages, int nFrames) {
    int *frames = (int *)malloc(nFrames * sizeof(int));
    int *recentlyUsed = (int *)malloc(nFrames * sizeof(int));
    int pageFaults = 0;

    // Initialize frames with -1 to indicate empty frame
    for (int i = 0; i < nFrames; i++) {
        frames[i] = -1;
        recentlyUsed[i] = 0; // Initialize recently used counter
    }

    for (int i = 0; i < nPages; i++) {
        if (!pageExists(pages[i], frames, nFrames)) {
            // Find the index of the least recently used page
            int lruIndex = findLRUIndex(recentlyUsed, nFrames);
            frames[lruIndex] = pages[i];
            recentlyUsed[lruIndex] = i + 1; // Update recently used counter
            pageFaults++;
        } else {
            // Update the recently used counter for the existing page
            for (int j = 0; j < nFrames; j++) {
                if (frames[j] == pages[i]) {
                    recentlyUsed[j] = i + 1;
                    break;
                }
            }
        }
    }

    printf("Page faults using LRU algorithm: %d\n", pageFaults);

    free(frames);
    free(recentlyUsed);
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

    simulateLRUPageReplacement(pages, nPages, nFrames);

    free(pages);
    return 0;
}
