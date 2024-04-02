#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t mutex, empty, full;

void wait(sem_t *sem) {
    while (sem_wait(sem) != 0);
}

void signal(sem_t *sem) {
    sem_post(sem);
}

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100; // For demonstration, generate a random item
        wait(&empty); // Wait for empty space in the buffer
        wait(&mutex); // Lock the critical section
        buffer[in] = item; // Put item into buffer
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // Update buffer index
        signal(&mutex); // Unlock the critical section
        signal(&full); // Signal that buffer is full
        sleep(1); // Sleep for some time
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    while (1) {
        wait(&full); // Wait for items in the buffer
        wait(&mutex); // Lock the critical section
        item = buffer[out]; // Get item from buffer
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Update buffer index
        signal(&mutex); // Unlock the critical section
        signal(&empty); // Signal that buffer is empty
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

