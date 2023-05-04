/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testgettimeofday.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:29:05 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/04 15:22:18 by avancoll         ###   ########.fr       */
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
		// pthread_mutex_lock(&mutex);
		mail++;
		// pthread_mutex_unlock(&mutex);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	struct timeval start, end;

	mail = 0;
	pthread_mutex_init(&mutex, NULL);
	gettimeofday(&start, NULL);
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
	gettimeofday(&end, NULL);
	printf("Time taken: %ld micro seconds\n",
	((end.tv_sec * 1000000 + end.tv_usec) -
	(start.tv_sec * 1000000 + start.tv_usec)));
	return (0);
}