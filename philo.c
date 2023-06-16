/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:02:20 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/16 17:14:00 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (argc != 5 && argc != 6)
		return (ft_error(NULL, 0));
	if (init_data(&table, argv))
		return (ft_error(NULL, 1));
	if (table.nb_philo == 0)
		return (0);
	if (init_philo(&table))
		return (ft_error(&table, 2));
	if (table.nb_philo == 1)
	{
		printf("[%ld] 1 has taken a fork.\n", get_time(table.start_time));
		ft_usleep(table.philo, table.time_to_die);
		printf("[%d] 1 died.\n", table.time_to_die);
		return (free_all(&table));
	}
	if (init_thread(&table))
		return (ft_error(&table, 3));
	i = -1;
	while (++i < table.nb_philo)
		pthread_join(table.thread[i], NULL);
	free_all(&table);
	return (0);
}
