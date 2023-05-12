/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:39:46 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/12 17:26:24 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_fork(pthread_mutex_t *fork1, pthread_mutex_t *fork2, int id, struct timeval time)
{
	pthread_mutex_lock(fork1);
	pthread_mutex_lock(fork2);
	printf("[%ld] Philosopher %d has taken a fork.\n", get_current_time(time), id + 1);
	printf("[%ld] Philosopher %d has taken a fork.\n", get_current_time(time), id + 1);
}

void	put_down_fork(pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
}

void	ft_think(int id, struct timeval time)
{
	printf("[%ld] Philosopher %d is thinking.\n", get_current_time(time), id + 1);
}

void	ft_eat(int id, struct timeval time, int time_to_eat, pthread_mutex_t *death)
{
	pthread_mutex_lock(death);
	printf("[%ld] Philosopher %d is eating.\n", get_current_time(time), id + 1);
	usleep(time_to_eat * 1000);
	pthread_mutex_unlock(death);
}

void	ft_sleep(int id, struct timeval time, int time_to_sleep)
{
	printf("[%ld] Philosopher %d is sleeping.\n", get_current_time(time), id + 1);
	usleep(time_to_sleep * 1000);
}
