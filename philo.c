/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:29:05 by avancoll          #+#    #+#             */
/*   Updated: 2023/03/20 15:11:07 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	mutex;
int				mail;
pthread_t		t1;
pthread_t		t2;

void	*routine(void *arg)
{
	(void)arg;
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		mail++;
		pthread_mutex_unlock(&mutex);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	mail = 0;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_join(t1, NULL) != 0)
		return (1);
	if (pthread_join(t2, NULL) != 0)
		return (1);
	pthread_mutex_destroy(&mutex);
	printf("%d\n", mail);
	return (0);
}