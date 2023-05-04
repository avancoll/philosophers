/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:29:20 by avancoll          #+#    #+#             */
/*   Updated: 2023/03/29 16:53:42 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	struct timeval	last_meal;
} t_philo;

void pick_up_fork(pthread_mutex_t *fork, int id)
{
	pthread_mutex_lock(fork);
	printf("Philosopher %d has taken a fork.\n", id);
}

void put_down_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

void think(int id)
{
	printf("Philosopher %d is thinking.\n", id);
}

void eat(int id)
{
	printf("Philosopher %d is eating.\n", id);
}

long get_current_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void* philosopher(void* arg)
{
	t_philo	*philo;
	long current_time;
	long time_since_last_meal;
	int	alive;

	philo = /*(t_philo*)*/ arg;
	alive = 1;
	while (alive)
	{
		think(philo->id);
		pick_up_fork(philo->left_fork);
		pick_up_fork(philo->right_fork);
		eat(philo->id);
		usleep(philo->time_to_eat);
		put_down_fork(philo->left_fork);
		put_down_fork(philo->right_fork);
		gettimeofday(&(philo->last_meal), NULL);
		usleep(philo->time_to_sleep);
		printf("Philosopher %d is sleeping.\n", philo->id);
		current_time = get_current_time();
		time_since_last_meal = current_time - (phil->last_meal.tv_sec * 1000000 + phil->last_meal.tv_usec);
		if (time_since_last_meal > philo->time_to_die)
		{
			printf("Philosopher %d has died.\n", philo->id);
			alive = 0;
		}
	}
	pthread_exit(NULL);
}

void init_philo(philosopher_t* philo, int id, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int time_to_die, int time_to_eat, int time_to_sleep)
{
	philo->id = id;
	philo->left_fork = left_fork;
	philo->right_fork = right_fork;
	philo->time_to_die = time_to_die;
	philo->time_to_eat = time_to_eat;
	philo->time_to_sleep = time_to_sleep;
	gettimeofday(&(philo->last_meal), NULL);
}

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		printf("Usage: ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep\n");
		return 1;
	}
	int num_philosophers = atoi(argv[1]);
	int time_to_die = atoi(argv[2]);
	int time_to_eat = atoi(argv[3]);
	int time_to_sleep = atoi(argv[4]);
pthread_mutex_t forks[num_philosophers];
for (int i = 0; i < num_philosophers; i++)
{
	pthread_mutex_init(&forks[i], NULL);
}
t_philo philo[num_philosophers];
for (int i = 0; i < num_philosophers; i++)
	init_philo(&philosophers[i], i, &forks[i], &forks[(i+1) % num_philosophers], time_to_die, time_to_eat, time_to_sleep);
pthread_t threads[num_philosophers];
for (int i = 0; i < num_philosophers; i++)
	pthread_create(&threads[i], NULL, philosopher, &philosophers[i]);
for (int i = 0; i < num_philosophers; i++)
	pthread_join(threads[i], NULL);
for (int i = 0; i < num_philosophers; i++)
	pthread_mutex_destroy(&forks[i]);
return 0;
}