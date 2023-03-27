/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:29:20 by avancoll          #+#    #+#             */
/*   Updated: 2023/03/27 17:15:21 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	counter = 0;
pthread_mutex_t	lock;

int	ft_atoi(const char *s, t_data *data)
{
	int						i;
	unsigned long long		res;
	int						sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign = -sign;
	if (!s[i])
		data->error = 1;
	while (s[i] == '0')
		i++;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		res = res * 10 + s[i++] - '0';
	if ((s[i] && (s[i] < '0' || s[i] > '9')) || (res > 2147483647 && sign == 1)
		|| (res > 2147483648 && sign == -1))
		data->error = 1;
	return (res * sign);
}

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

void* routine(void *arg)
{
	(void)arg;
	pthread_mutex_lock(&lock);

	unsigned long i = 0;
	counter += 1;
	printf("\n Job %d started\n", counter);
	for(i=0; i<(0xFFFFFFFF);i++);
	printf("\n Job %d finished\n", counter);
	pthread_mutex_unlock(&lock);
	return NULL;
}

int	init_philo(t_data data)
{
	int			i;
	t_philo		philo;

	pthread_mutex_init(&lock, NULL);
	i = -1;
	while (++i < data.n_philo)
	{
		pthread_create(&(philo.t), NULL, &routine, NULL);
		pthread_join(philo.t, NULL);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (1);
	if (init_data(&data, argv))
		return (1);
	printf("n_philo = %d\ntime_to_die = %d\ntime_to_eat = %d\ntime_to_sleep = %d\nn_eat = %d\n", data.n_philo, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.n_eat);
	init_philo(data);
	return (0);
}
