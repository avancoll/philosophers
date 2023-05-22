/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:02:20 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/22 19:14:36 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_table(t_table *table)
{
	if (table->philo)
		free(table->philo);
	if (table->forks)
		free(table->forks);
	if (table->thread)
		free(table->thread);
	if (table->print)
		free(table->print);
	return (0);
}

int	ft_error(t_table *table, int errnum)
{
	if (errnum == 0)
		printf("Error: Wrong number of arguments.\n");
	else if (errnum == 1)
		printf("Error: Wrong arguments.\n");
	else if (errnum == 2)
	{
		free_table(table);
		printf("Error: Malloc failed.\n");
	}
	else if (errnum == 3)
		printf("Error: Thread failed.\n");
	return (1);
}

int	free_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(table->print);
	free_table(table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (ft_error(NULL, 0));
	if (init_data(&table, argv))
		return (ft_error(NULL, 1));
	if (table.nb_philo == 1)
	{
		printf("[%ld] 1 has taken a fork.\n", get_time(table.start_time));
		printf("[%ld] 1 died.\n", get_time(table.start_time));
		return (0);
	}
	if (init_philo(&table))
		return (ft_error(&table, 2));
	if (init_thread(&table))
		return (ft_error(NULL, 3));
	free_all(&table);
	return (0);
}
