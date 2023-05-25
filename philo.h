/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:01:54 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/25 12:22:57 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				nb_ate;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
	struct timeval	last_eat;
}	t_philo;

struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		*thread;
	pthread_mutex_t	*print;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				check_death;
	int				error;
	struct timeval	start_time;
};

int		init_data(t_table *table, char **argv);
int		init_philo(t_table *table);
int		init_thread(t_table *table);
void	*routine(void *arg);
int		ft_atoi(char *s, t_table *table);
int		ft_check_death(t_table *table);
int		ft_check_eat(t_table *table);
long	get_time(struct timeval start_time);
void	death(t_philo *philo);
void	pick_up_fork(t_philo *philo);
void	put_down_fork(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	action_printer(t_philo *philo, int action);
void	ft_usleep(t_philo *philo, int ms);
int		free_all(t_table *table);
int		ft_error(t_table *table, int errnum);

#endif
