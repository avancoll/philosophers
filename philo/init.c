/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:01:08 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/12 17:28:35 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **argv)
{
	data->num_philosophers = ft_atoi(argv[1], data);
	data->time_to_die = ft_atoi(argv[2], data);
	data->time_to_eat = ft_atoi(argv[3], data);
	data->time_to_sleep = ft_atoi(argv[4], data);
	if (argv[5])
		data->n_eat = ft_atoi(argv[5], data);
	if (data->error)
		return (1);
	return (0);
}

void	init_philo(t_philo *philo, int id, pthread_mutex_t *forks, t_data data)
{
	philo[id].id = id;
	philo[id].left_fork = &forks[id];
	philo[id].right_fork = &forks[(id + 1) % data.num_philosophers];
	philo[id].death = philo->death;
	philo[id].time_to_die = data.time_to_die;
	philo[id].time_to_eat = data.time_to_eat;
	philo[id].time_to_sleep = data.time_to_sleep;
	gettimeofday(&(philo[id].last_meal), NULL);
	gettimeofday(&(philo[id].start_time), NULL);
}