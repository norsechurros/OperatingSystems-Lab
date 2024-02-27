//to compile run gcc -o q1 q1.c -pthread -lrt


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t mutex, empty, full;

void *producer(void *arg) {
    int item;
    for (int i = 0; i < MAX_ITEMS; ++i) {
        item = i; // Produce item
        sem_wait(&empty); // Wait for empty space in the buffer
        sem_wait(&mutex); // Lock the critical section
        buffer[in] = item; // Put item into buffer
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // Update buffer index
        sem_post(&mutex); // Unlock the critical section
        sem_post(&full); // Signal that buffer is full
        sleep(1); // Sleep for some time
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < MAX_ITEMS; ++i) {
        sem_wait(&full); // Wait for items in the buffer
        sem_wait(&mutex); // Lock the critical section
        item = buffer[out]; // Get item from buffer
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Update buffer index
        sem_post(&mutex); // Unlock the critical section
        sem_post(&empty); // Signal that buffer is empty
        sleep(1); // Sleep for some time
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Join threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
