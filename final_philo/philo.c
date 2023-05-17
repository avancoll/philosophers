/* ************************************************************************** */
/*														                    */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:16:49 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/17 14:38:33 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(struct timeval start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - (start_time.tv_sec * 1000 + start_time.tv_usec / 1000));
}

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

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = - 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	return (nb * neg);
}


int	init_data(t_table *table, char **argv)
{
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->nb_eat = ft_atoi(argv[5]);
	table->check_death = 0;
	return (0);
}

int	init_philo(t_table *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	table->print = malloc(sizeof(pthread_mutex_t));
	table->thread = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!table->philo || !table->forks || !table->thread)
		return (1);
	while (++i < table->nb_philo)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		table->philo[i].id = i;
		table->philo[i].nb_eat = 0;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
		table->philo[i].table = table;
	}
	return (0);
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

int	init_thread(t_table *table)
{
	int	i;

	i = -1;
	gettimeofday(&(table->start_time), NULL);
	while (++i < table->nb_philo)
		pthread_create(&(table->thread[i]), NULL, routine, &table->philo[i]);
	i = -1;
	while (++i < table->nb_philo)
		pthread_join(table->thread[i], NULL);
	return (0);
}


int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5)
		return (1);
	if (init_data(&table, argv))
		return (1);
	if (init_philo(&table))
		return (1);
	if (init_thread(&table))
		return (1);
	return (0);
}
