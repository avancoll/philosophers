/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:29:20 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/04 15:21:11 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1], data);
	data->time_to_die = ft_atoi(argv[2], data);
	data->time_to_eat = ft_atoi(argv[3], data);
	data->time_to_sleep = ft_atoi(argv[4], data);
	if (argv[5])
		data->n_eat = ft_atoi(argv[5], data);
	if (data->error)
		return (1);
	return (0);
}

int	init_philo(t_data data)
{
	int			i;
	// t_philo		philo;

	i = -1;
	while (++i < data.n_philo)
		pthread_mutex_init(&forks[i], NULL);
	i = -1;
	while (++i < data.n_philo)
	{
		pthread_create(&(philosopher[i]), NULL, &routine, NULL);
		pthread_join(philosopher[i], NULL);
	}
	return (0);
}

void init_philo(t_philo *philo, t_data data, it id)
{
	philo->id = id;
	philo->left_fork = data->left_fork;
	philo->right_fork = data->right_fork;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	gettimeofday(&(philo->last_meal), NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_data(&data, argv))
		return (1);
	init_philo(data);
	return (0);
}
