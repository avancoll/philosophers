/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:39:46 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/04 16:04:36 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_fork(pthread_mutex_t *fork, int id)
{
	pthread_mutex_lock(fork);
	printf("%ld Philosopher %d has taken a fork.\n", get_current_time(), id);
}

void	put_down_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

void	think(int id)
{
	printf("%ld Philosopher %d is thinking.\n", get_current_time(), id);
}

void	eat(int id)
{
	printf("%ld Philosopher %d is eating.\n", get_current_time(), id);
}
