/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:15:21 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/10 17:08:13 by avancoll         ###   ########.fr       */
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

typedef struct s_data
{
	int	num_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_eat;
	int	error;
}		t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct timeval	last_meal;
	struct timeval	start_time;
}	t_philo;

int		ft_atoi(const char *s, t_data *data);
long	get_current_time(struct timeval start);
void	pick_up_fork(pthread_mutex_t *fork1, pthread_mutex_t *fork2, int id, struct timeval time);
void	put_down_fork(pthread_mutex_t *fork);
void	think(int id, struct timeval time);
void	eat(int id, struct timeval time);
int	init_data(t_data *data, char **argv);
void	init_philo(t_philo *philo, int id, pthread_mutex_t *forks, t_data data);

#endif
