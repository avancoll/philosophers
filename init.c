/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:09:38 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/25 19:46:08 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_table *table, char **argv)
{
	table->nb_philo = ft_atoi(argv[1], table);
	table->time_to_die = ft_atoi(argv[2], table);
	table->time_to_eat = ft_atoi(argv[3], table);
	table->time_to_sleep = ft_atoi(argv[4], table);
	gettimeofday(&(table->start_time), NULL);
	if (argv[5])
		table->nb_eat = ft_atoi(argv[5], table);
	else
		table->nb_eat = -1;
	table->check_death = 0;
	if (table->error == 1)
		return (1);
	return (0);
}

int	init_philo(t_table *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	table->print = malloc(sizeof(pthread_mutex_t));
	table->death = malloc(sizeof(pthread_mutex_t));
	table->thread = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!table->philo || !table->forks || !table->print
		|| !table->thread || !table->death)
		return (1);
	pthread_mutex_init(table->print, NULL);
	pthread_mutex_init(table->death, NULL);
	while (++i < table->nb_philo)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		table->philo[i].id = i;
		table->philo[i].nb_ate = 0;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
		table->philo[i].table = table;
		table->philo[i].last_eat = table->start_time;
	}
	return (0);
}

int	init_thread(t_table *table)
{
	int	i;
	int	check;

	i = -1;
	while (++i < table->nb_philo)
		if (pthread_create(&(table->thread[i]), NULL, routine,
				&table->philo[i]))
			return (1);
	check = 1;
	while (check)
	{
		i = -1;
		while (++i < table->nb_philo && check)
		{
			if (get_time(table->philo[i].last_eat) >= table->time_to_die)
			{
				action_printer(&table->philo[i], 3);
				pthread_mutex_lock(table->death);
				table->check_death = 1;
				pthread_mutex_unlock(table->death);
				check = 0;
			}
		}
	}
	return (0);
}
