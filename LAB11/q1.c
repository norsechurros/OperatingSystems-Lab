#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparison function for qsort()
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void SSTF(int queue[], int rw_head, int rw_tail) {
    int rwi = 0;
    int n = rw_tail;
    qsort(queue, n, sizeof(int), compare);

    for (int i = 0; i < n; i++) {
        if (rw_head > queue[i]) {
            rwi++;
        }
    }

    for (int i = rwi; i < n; i++) {
        if (i < n - 1) {
            if (abs(rw_head - queue[i]) > abs(rw_head - queue[i + 1])) {
                printf("head at %d\n", queue[i]);
            } else {
                printf("head at %d\n", queue[i]);
            }
        } else {
            printf("head at %d\n", queue[i]);
        }
    }
}

void SCAN(int queue[], int rw_head, int rw_tail) {
    int n = rw_tail;
    qsort(queue, n, sizeof(int), compare);

    int rwi = 0;
    for (int i = 0; i < n; i++) {
        if (rw_head > queue[i]) {
            rwi++;
        }
    }

    for (int i = rwi; i < n; i++) {
        printf("head at %d\n", queue[i]);
    }
    for (int i = rwi - 1; i >= 0; i--) {
        printf("head at %d\n", queue[i]);
    }
}

void CSCAN(int queue[], int rw_head, int rw_tail) {
    int n = rw_tail;
    qsort(queue, n, sizeof(int), compare);

    int rwi = 0;
    for (int i = 0; i < n; i++) {
        if (rw_head > queue[i]) {
            rwi++;
        }
    }

    for (int i = rwi; i < n; i++) {
        printf("head at %d\n", queue[i]);
    }
    for (int i = 0; i < rwi; i++) {
        printf("head at %d\n", queue[i]);
    }
}

void CLOOK(int queue[], int rw_head, int rw_tail) {
    int n = rw_tail;
    qsort(queue, n, sizeof(int), compare);

    int rwi = 0;
    for (int i = 0; i < n; i++) {
        if (rw_head > queue[i]) {
            rwi++;
        }
    }

    for (int i = rwi; i < n; i++) {
        printf("head at %d\n", queue[i]);
    }
    for (int i = 0; i < rwi; i++) {
        printf("head at %d\n", queue[i]);
    }
}

int main() {
    int ch, len, rwh, rwt;
    int arr[100];
    printf("Disk Scheduling Algorithms\n");
    printf("1. SSTF\n");
    printf("2. SCAN\n");
    printf("3. C-SCAN\n");
    printf("4. C-LOOK\n");
    printf("Enter choice: ");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            printf("Enter length of queue: ");
            scanf("%d", &len);
            printf("Enter queue: ");
            for (int i = 0; i < len; i++) {
                scanf("%d", &arr[i]);
            }
            printf("Enter Read-Write Head and Tail: ");
            scanf("%d,%d", &rwh, &rwt);
            SSTF(arr, rwh, rwt);
            break;
        case 2:
            printf("Enter length of queue: ");
            scanf("%d", &len);
            printf("Enter queue: ");
            for (int i = 0; i < len; i++) {
                scanf("%d", &arr[i]);
            }
            printf("Enter Read-Write Head and Tail: ");
            scanf("%d,%d", &rwh, &rwt);
            SCAN(arr, rwh, rwt);
            break;
        case 3:
            printf("Enter length of queue: ");
            scanf("%d", &len);
            printf("Enter queue: ");
            for (int i = 0; i < len; i++) {
                scanf("%d", &arr[i]);
            }
            printf("Enter Read-Write Head and Tail: ");
            scanf("%d,%d", &rwh, &rwt);
            CSCAN(arr, rwh, rwt);
            break;
        case 4:
            printf("Enter length of queue: ");
            scanf("%d", &len);
            printf("Enter queue: ");
            for (int i = 0; i < len; i++) {
                scanf("%d", &arr[i]);
            }
            printf("Enter Read-Write Head and Tail: ");
            scanf("%d,%d", &rwh, &rwt);
            CLOOK(arr, rwh, rwt);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}

/*
OUTPUT:

Disk Scheduling Algorithms
1. SSTF
2. SCAN
3. C-SCAN
4. C-LOOK
Enter choice: 2
Enter length of queue: 8
Enter queue: 98 183 37 122 14 124 65 67
Enter Read-Write Head and Tail: 53,199
head at 65
head at 67
head at 98
head at 122
head at 124
head at 124
head at 124
head at 124
head at 122
head at 98
head at 67
head at 65
head at 53


*/
