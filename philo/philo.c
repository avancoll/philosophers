/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:28:06 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/08 17:18:39 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **argv)
{
	data->num_philosophers = ft_atoi(argv[1], data);
	data->time_to_die = ft_atoi(argv[2], data);
	data->time_to_eat = ft_atoi(argv[3], data);
	data->time_to_sleep = ft_atoi(argv[4], data);
	if (argv[5])
		data->n_eat = ft_atoi(argv[5], data);
	if (data->error)
		return (1);
	return (0);
}

void	init_philo(t_philo *philo, int id, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int time_to_die, int time_to_eat, int time_to_sleep)
{
	philo->id = id;
	philo->left_fork = left_fork;
	philo->right_fork = right_fork;
	philo->time_to_die = time_to_die;
	philo->time_to_eat = time_to_eat;
	philo->time_to_sleep = time_to_sleep;
	gettimeofday(&(philo->last_meal), NULL);
	gettimeofday(&(philo->time), NULL);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	long	time_since_last_meal;
	struct timeval x;
	// int		alive = 10;
	philo = arg;
	while (1)
	{
		think(philo->id, philo->time);
		pick_up_fork(philo->left_fork, philo->id, philo->time);
		pick_up_fork(philo->right_fork, philo->id, philo->time);
		eat(philo->id, philo->time);
		usleep(philo->time_to_eat * 1000);
		put_down_fork(philo->left_fork);
		put_down_fork(philo->right_fork);
		gettimeofday(&(philo->last_meal), NULL);
		usleep(philo->time_to_sleep * 1000);
		printf("%ld Philosopher %d is sleeping.\n", get_current_time(philo->time), philo->id);
		gettimeofday(&x, NULL);
		time_since_last_meal = (x.tv_sec * 1000 + x.tv_usec / 1000) - (philo->last_meal.tv_sec * 1000 + philo->last_meal.tv_usec / 1000);
		// printf("time_since_last_meal  = %ld\n", time_since_last_meal);
		if (time_since_last_meal > philo->time_to_die)
		{
			printf("%ld Philosopher %d has died.\n", get_current_time(philo->time), philo->id);
			break;
		}
	}
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5)
		return 1;
	if (init_data(&data, argv))
		return (1);
	pthread_mutex_t	forks[data.num_philosophers];
	i = -1;
	while (++i < data.num_philosophers)
		pthread_mutex_init(&forks[i], NULL);
	t_philo	philo[data.num_philosophers];
	i = -1;
	while (++i < data.num_philosophers)
		init_philo(&philo[i], i, &forks[i], &forks[(i + 1) % data.num_philosophers], data.time_to_die, data.time_to_eat, data.time_to_sleep);
	pthread_t thread[data.num_philosophers];
	i = -1;
	while (++i < data.num_philosophers)
		pthread_create(&thread[i], NULL, philosopher, &philo[i]);
	i = -1;
	while (++i < data.num_philosophers)
		pthread_join(thread[i], NULL);
	i = -1;
	while (++i < data.num_philosophers)
		pthread_mutex_destroy(&forks[i]);
	return 0;
}