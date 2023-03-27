/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:15:21 by avancoll          #+#    #+#             */
/*   Updated: 2023/03/27 15:26:30 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep,
# include <sys/time.h> // gettimeofday
# include <pthread.h> // pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

typedef struct s_philo
{
	pthread_t		t;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
}			t_philo;

typedef	struct s_data
{
	int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_eat;
	int	error;
	t_philo	*philo;
}		t_data;

#endif
