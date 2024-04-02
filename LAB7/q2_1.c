#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, write_sem; // Renamed the variable

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);
        sem_wait(&write_sem);
        printf("Reading...\n");
        sem_post(&mutex);
        sem_post(&write_sem);
        sleep(1);
    }
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&write_sem);
        printf("Writing...\n");
        sem_post(&write_sem);
        sleep(1);
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    sem_init(&mutex, 0, 1);
    sem_init(&write_sem, 0, 1);

    for (int i = 0; i < NUM_READERS; i++)
        pthread_create(&readers[i], NULL, reader, NULL);

    for (int i = 0; i < NUM_WRITERS; i++)
        pthread_create(&writers[i], NULL, writer, NULL);

    for (int i = 0; i < NUM_READERS; i++)
        pthread_join(readers[i], NULL);

    for (int i = 0; i < NUM_WRITERS; i++)
        pthread_join(writers[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&write_sem);

    return 0;
}


/*./q2_1 
Reading...
Writing...
Writing...
Reading...
Reading...
Writing...
Reading...
Writing...
Reading...
Reading...
Writing...
Reading...
Reading...
Reading...
Writing...*/
