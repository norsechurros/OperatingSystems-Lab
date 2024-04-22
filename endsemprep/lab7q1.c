#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int buffer[10];
int in =0,out =0;
sem_t mutex, empty, full;

void *producer(void *arg)
{
	int item;
	for(int i =0;i<15;i++)
	{
		item = i;
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in] = item;
		
		printf("Produced: %d",&item);
		in = (in+1)%10;
		
		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}
	p_thread_exit(NULL);
}

void *consumer(void *arg)
{
	int item;
	for(int i =0;i<15;i++)
	{
		item = i;
		sem_wait(&full);
		sem_wait(&mutex);
		item = buffer[out];
		
		printf("Consumer: %d",&item);
		out = (out+1)%10;
		
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1);
	}
	p_thread_exit(NULL);
}
