/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:05:39 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/23 14:39:28 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_printer(t_philo *philo, int action)
{
	long	time;

	time = get_time(philo->table->start_time);
	pthread_mutex_lock(philo->table->print);
	if (philo->table->check_death == 0 && (philo->nb_ate < philo->table->nb_eat
			|| philo->table->nb_eat == -1))
	{
		if (action == 0)
		{
			printf("[%ld] %d has taken a fork.\n", time, philo->id + 1);
			printf("[%ld] %d has taken a fork.\n", time, philo->id + 1);
			printf("[%ld] %d is eating.\n", time, philo->id + 1);
			philo->nb_ate++;
		}
		else if (action == 1)
			printf("[%ld] %d is sleeping.\n", time, philo->id + 1);
		else if (action == 2)
			printf("[%ld] %d is thinking.\n", time, philo->id + 1);
		else if (action == 3)
		{
			philo->table->check_death = 1;
			printf("[%ld] %d died.\n", time, philo->id + 1);
		}
	}
	pthread_mutex_unlock(philo->table->print);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	struct timeval	current_time;

	philo = arg;
	if (!(philo->id & 1))
		usleep(100);
	while (philo->table->check_death == 0 && (philo->nb_ate
			< philo->table->nb_eat || philo->table->nb_eat == -1))
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		action_printer(philo, 0);
		gettimeofday(&(philo->last_eat), NULL);
		ft_usleep(philo->table->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		action_printer(philo, 1);
		ft_usleep(philo->table->time_to_sleep);
		gettimeofday(&current_time, NULL);
		if (get_time(philo->last_eat) >= philo->table->time_to_die)
			action_printer(philo, 3);
		action_printer(philo, 2);
	}
	return (0);
}
