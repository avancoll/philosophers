/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:19:04 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/16 13:24:14 by avancoll         ###   ########.fr       */
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
	if (table->death)
		free(table->death);
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
	{
		free_table(table);
		printf("Error: Thread failed.\n");
	}
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
