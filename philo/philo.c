/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:28:06 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/04 17:00:03 by avancoll         ###   ########.fr       */
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
	printf("id = %d\n", id);
	philo->left_fork = left_fork;
	philo->right_fork = right_fork;
	philo->time_to_die = time_to_die;
	philo->time_to_eat = time_to_eat;
	philo->time_to_sleep = time_to_sleep;
	gettimeofday(&(philo->last_meal), NULL);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;
	long	current_time;
	long	time_since_last_meal;

	philo = arg;
	while (1)
	{
		think(philo->id);
		pick_up_fork(philo->left_fork, philo->id);
		pick_up_fork(philo->right_fork, philo->id);
		eat(philo->id);
		usleep(philo->time_to_eat);
		put_down_fork(philo->left_fork);
		put_down_fork(philo->right_fork);
		gettimeofday(&(philo->last_meal), NULL);
		usleep(philo->time_to_sleep);
		printf("%ld Philosopher %d is sleeping.\n", get_current_time(), philo->id);
		current_time = get_current_time();
		time_since_last_meal = current_time - (philo->last_meal.tv_sec * 1000000 + philo->last_meal.tv_usec);
		if (time_since_last_meal > philo->time_to_die)
		{
			printf("%ld Philosopher %d has died.\n", get_current_time(), philo->id);
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
		init_philo(&philo[i], i, &forks[i], &forks[(i+1) % data.num_philosophers], data.time_to_die, data.time_to_eat, data.time_to_sleep);
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