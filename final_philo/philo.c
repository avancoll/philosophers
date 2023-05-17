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

void	pick_up_fork(pthread_mutex_t *fork1, pthread_mutex_t *fork2, int id)
{
	pthread_mutex_lock(fork1);
	pthread_mutex_lock(fork2);
	printf("[] Philosopher %d has taken a fork.\n", id + 1);
	printf("[] Philosopher %d has taken a fork.\n", id + 1);
}

void	put_down_fork(pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
}

void	ft_think(int id)
{
	printf("[] Philosopher %d is thinking.\n", id + 1);
}

void	ft_eat(int id, int time_to_eat)
{
	printf("[] Philosopher %d is eating.\n",  id + 1);
	usleep(time_to_eat * 1000);
}

void	ft_sleep(int id, int time_to_sleep)
{
	printf("[] Philosopher %d is sleeping.\n", id + 1);
	usleep(time_to_sleep * 1000);
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
	table->thread = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!table->philo || !table->forks || !table->thread)
		return (1);
	while (++i < table->nb_philo)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		table->philo[i].id = i;
		table->philo[i].nb_eat = 0;
		table->philo[i].last_eat = 0;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
	}
	return (0);
}

void	*routine(void *arg)
{
	t_table	*table;
	int		id;

	table = arg;
	if (!(id & 1))
		usleep(100);
	return (0);
}

int	init_thread(t_table *table)
{
	int	i;
	i = -1;
	while (++i < table->nb_philo)
		pthread_create(&(table->thread[i]), NULL, routine, table);
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
