/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:28:06 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/12 17:27:29 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;
	long	time_since_last_meal;
	struct timeval x;

	philo = arg;
	if (!(philo->id & 1))
		usleep(100);
	while (1)
	{
		gettimeofday(&(philo->last_meal), NULL);
		pick_up_fork(philo->left_fork, philo->right_fork, philo->id, philo->start_time);
		ft_eat(philo->id, philo->start_time, philo->time_to_eat, philo->death);
		put_down_fork(philo->left_fork, philo->right_fork);
		ft_sleep(philo->id, philo->start_time, philo->time_to_sleep);
		gettimeofday(&x, NULL);
		time_since_last_meal = (x.tv_sec * 1000 + x.tv_usec / 1000) - (philo->last_meal.tv_sec * 1000 + philo->last_meal.tv_usec / 1000);
		if (time_since_last_meal >= philo->time_to_die)
		{
			pthread_mutex_lock(philo->death);
			printf("[%ld] Philosopher %d has died.\n", get_current_time(philo->start_time), philo->id + 1);
			break;
		}
		ft_think(philo->id + 1, philo->start_time);
	}
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		*thread;
	int				i;

	if (argc != 5)
		return 1;
	if (init_data(&data, argv))
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * data.num_philosophers);
	philo = malloc(sizeof(t_philo) * data.num_philosophers);
	thread = malloc(sizeof(pthread_t) * data.num_philosophers);
	philo->death = malloc(sizeof(pthread_mutex_t));
	i = -1;
	while (++i < data.num_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		init_philo(philo, i, forks, data);
	}
	i = -1;
	while (++i < data.num_philosophers)
		pthread_create(&thread[i], NULL, philosopher, &philo[i]);
	i = -1;
	while (++i < data.num_philosophers)
		pthread_join(thread[i], NULL);
/*
	i = -1;
	while (++i < data.num_philosophers)
		pthread_mutex_destroy(&forks[i]);
*/
	return 0;
}