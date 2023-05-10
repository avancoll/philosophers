#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 10

pthread_mutex_t forks[MAX_PHILOSOPHERS];
pthread_t philosophers[MAX_PHILOSOPHERS];
int num_philosophers;
int time_to_die;
int time_to_eat;
int time_to_sleep;

void	grab_forks(int philosopher_id)
{
	pthread_mutex_lock(&forks[philosopher_id]);
	pthread_mutex_lock(&forks[(philosopher_id + 1) % num_philosophers]);
	printf("Philosopher %d has taken a fork.\n", philosopher_id);
	printf("Philosopher %d has taken a fork.\n", philosopher_id);
}

void	release_forks(int philosopher_id)
{
	pthread_mutex_unlock(&forks[philosopher_id]);
	pthread_mutex_unlock(&forks[(philosopher_id + 1) % num_philosophers]);
}

void	*philosopher(void *arg)
{
	int philosopher_id = *(int*)arg;
	struct timeval start_time, curr_time;
	while (1)
	{
		gettimeofday(&start_time, NULL);
		grab_forks(philosopher_id);
		gettimeofday(&curr_time, NULL);
		unsigned long time_elapsed = (curr_time.tv_sec - start_time.tv_sec) * 1000 + (curr_time.tv_usec - start_time.tv_usec) / 1000;
		printf("Philosopher %d is eating.\n", philosopher_id);
		usleep(time_to_eat * 1000);
		release_forks(philosopher_id);
		printf("Philosopher %d is sleeping.\n", philosopher_id);
		usleep(time_to_sleep * 1000);
		gettimeofday(&curr_time, NULL);
		unsigned long total_time = (curr_time.tv_sec - start_time.tv_sec) * 1000 + (curr_time.tv_usec - start_time.tv_usec) / 1000;
		if (total_time >= time_to_die)
		{
			printf("Philosopher %d died.\n", philosopher_id);
			break;
		}
		printf("Philosopher %d is thinking.\n", philosopher_id);
	}
	return (NULL);
}

int	main(int argc, char** argv)
{
	if (argc != 5)
		return (1);
	num_philosophers = atoi(argv[1]);
	time_to_die = atoi(argv[2]);
	time_to_eat = atoi(argv[3]);
	time_to_sleep = atoi(argv[4]);
	int i;
	for (i = 0; i < num_philosophers; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
	}
	for (i = 0; i < num_philosophers; i++)
	{
		int *philosopher_id = malloc(sizeof(int));
		*philosopher_id = i;
		pthread_create(&philosophers[i], NULL, philosopher, philosopher_id);
		pthread_detach(philosophers[i]);
	}
	sleep(time_to_die);
	for (i = 0; i < num_philosophers; i++)
	{
		pthread_mutex_destroy(&forks[i]);
	}
	return 0;
}

