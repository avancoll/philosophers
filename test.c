#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* routine(void *arg)
{
	pthread_mutex_lock(&lock);

	unsigned long i = 0;
	counter += 1;
	printf("\n Job %d started\n", counter);
	for(i=0; i<(0xFFFFFFFF);i++);
	printf("\n Job %d finished\n", counter);
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(void)
{
	int	i = 0;
	int err;

	pthread_mutex_init(&lock, NULL);
	while(i < 2)
	{
		pthread_create(&(tid[i]), NULL, &routine, NULL);
		i++;
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_mutex_destroy(&lock);

	return 0;
}