/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:09:03 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/23 17:57:36 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(struct timeval start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- (start_time.tv_sec * 1000 + start_time.tv_usec / 1000));
}

int	ft_atoi(char *s, t_table *table)
{
	int						i;
	unsigned long long		res;

	i = 0;
	res = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			table->error = 1;
	if (!s[i])
		table->error = 1;
	while (s[i] == '0')
		i++;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		res = res * 10 + s[i++] - '0';
	if ((s[i] && (s[i] < '0' || s[i] > '9')) || (res > 2147483647))
		table->error = 1;
	return (res);
}

void	ft_usleep(int ms)
{
	long	start;
	struct timeval start_time;

	gettimeofday(&start_time, NULL);
	start = get_time(start_time);
	while (get_time(start_time) - start < ms)
		usleep(100);
}

void	ft_usleep_test(t_philo *philo, int ms)
{
	long	start;
	struct timeval start_time;

	gettimeofday(&start_time, NULL);
	start = get_time(start_time);
	while (get_time(start_time) - start < ms)
	{
		if (get_time(philo->last_eat) >= philo->table->time_to_die)
		{
			action_printer(philo, 3);
			return ;
		}
		usleep(100);
	}
}
