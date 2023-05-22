/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:05:39 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/22 17:02:43 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death(t_philo *philo)
{
	pthread_mutex_lock(philo->table->print);
	if (philo->table->check_death == 1)
		return ;
	printf("[%ld] %d died.\n", get_time(philo->table->start_time), philo->id + 1);
	philo->table->check_death = 1;
	usleep(1000);
	pthread_mutex_unlock(philo->table->print);
}

void	pick_up_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	if (philo->table->check_death == 1)
		return ;
	pthread_mutex_lock(philo->table->print);
	printf("[%ld] %d has taken a fork.\n", get_time(philo->table->start_time), philo->id + 1);
	printf("[%ld] %d has taken a fork.\n", get_time(philo->table->start_time), philo->id + 1);
	pthread_mutex_unlock(philo->table->print);
}

void	put_down_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_think(t_philo *philo)
{
	if (philo->table->check_death == 1)
		return ;
	pthread_mutex_lock(philo->table->print);
	printf("[%ld] %d is thinking.\n", get_time(philo->table->start_time), philo->id + 1);
	pthread_mutex_unlock(philo->table->print);
}

void	ft_eat(t_philo *philo)
{
	if (philo->table->check_death == 1)
		return ;
	pthread_mutex_lock(philo->table->print);
	printf("[%ld] %d is eating.\n", get_time(philo->table->start_time), philo->id + 1);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->table->print);
}

void	ft_sleep(t_philo *philo)
{
	if (philo->table->check_death == 1)
		return ;
	pthread_mutex_lock(philo->table->print);
	printf("[%ld] %d is sleeping.\n", get_time(philo->table->start_time),  philo->id + 1);
	usleep(philo->table->time_to_sleep * 1000);
	pthread_mutex_unlock(philo->table->print);
}

void	action_printer(t_philo *philo, int action)
{
	pthread_mutex_lock(philo->table->print);
	if (action == 0)
		printf("[%ld] %d has taken a fork.\n", get_time(philo->table->start_time), philo->id + 1);
	else if (action == 1)
		printf("[%ld] %d is eating.\n", get_time(philo->table->start_time), philo->id + 1);
	else if (action == 2)
		printf("[%ld] %d is sleeping.\n", get_time(philo->table->start_time), philo->id + 1);
	else if (action == 3)
		printf("[%ld] %d is thinking.\n", get_time(philo->table->start_time), philo->id + 1);
	else if (action == 4)
		printf("[%ld] %d died.\n", get_time(philo->table->start_time), philo->id + 1);
	pthread_mutex_unlock(philo->table->print);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	struct timeval	current_time;

	philo = arg;
	if (!(philo->id & 1))
		usleep(1000);
	while (philo->table->check_death == 0)
	{
		gettimeofday(&(philo->last_eat), NULL);
		pick_up_fork(philo);
		ft_eat(philo);
		put_down_fork(philo);
		ft_sleep(philo);
		gettimeofday(&current_time, NULL);
		if (get_time(philo->last_eat) >= philo->table->time_to_die)
		{
			death(philo);
			break;
		}
		ft_think(philo);
	}
	return (0);
}
