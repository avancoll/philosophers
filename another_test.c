/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:59:17 by avancoll          #+#    #+#             */
/*   Updated: 2023/05/16 19:57:36 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_table t_table;

typedef struct s_philo
{
    t_table         *table;
    int				id;
    int				nb_eat;
    pthread_t		*thread;
    pthread_mutex_t	*forks;
    long long        last_eat;
}	t_philo;

typedef struct s_table
{
    t_philo         *philo;
    pthread_mutex_t	print;
    pthread_mutex_t	*forks;
    pthread_t		*thread;
    int				nb_philo;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				nb_eat;
    int				start;
    int				check_death;
    long long		start_time;
};

int ft_atoi(char *str)
{
    int	i;
    int	nb;
    int	neg;

    i = 0;
    nb = 0;
    neg = 1;
    while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\r'
        || str[i] == '\f' || str[i] == ' ')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            neg = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        nb = nb * 10 + (str[i] - 48);
        i++;
    }
    return (nb * neg);
}

int get_time(void)
{
    struct timeval	time;
    int				ret;

    gettimeofday(&time, NULL);
    ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (ret);
}

void    print_msg(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->print);
    printf("%d %d %s\n", get_time() - philo->start, philo->id, msg);
    pthread_mutex_unlock(&philo->print);
}

void    *check_death(void *arg)
{
    t_philo	*philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (get_time() - philo->start > philo->time_to_die)
        {
            print_msg(philo, "died");
            return (NULL);
        }
        if (philo->nb_eat != -1 && philo->id == philo->nb_eat)
            return (NULL);
        usleep(1000);
    }
}

void    *eat(t_philo *philo)
{
    pthread_t	death;

    pthread_create(&death, NULL, (void *)check_death, philo);
    while (1)
    {
        pthread_mutex_lock(&philo->forks[philo->id]);
        pthread_mutex_lock(&philo->forks[(philo->id + 1) % philo->nb_philo]);
        print_msg(philo, "has taken a fork");
        print_msg(philo, "has taken a fork");
        print_msg(philo, "is eating");
        usleep(philo->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->forks[philo->id]);
        pthread_mutex_unlock(&philo->forks[(philo->id + 1) % philo->nb_philo]);
        if (philo->nb_eat != -1)
            philo->nb_eat--;
        if (philo->nb_eat == 0)
            return (NULL);
        print_msg(philo, "is sleeping");
        usleep(philo->time_to_sleep * 1000);
        print_msg(philo, "is thinking");
    }
    return (NULL);
}

int	create_thread(t_philo *philo)
{
    int	i;

    i = 0;
    philo->thread = malloc(sizeof(pthread_t) * philo->nb_philo);
    if (!philo->thread)
        return (1);
    while (i < philo->nb_philo)
    {
        philo->id = i;
        if (pthread_create(&philo->thread[i], NULL, (void *)eat, philo) != 0)
            return (1);
        i++;
    }
    return (0);
}

int	create_mutex(t_philo *philo)
{
    int	i;

    i = 0;
    philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
    if (!philo->forks)
        return (1);
    while (i < philo->nb_philo)
    {
        if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    if (pthread_mutex_init(&philo->print, NULL) != 0)
        return (1);
    return (0);
}

void	destroy_mutex(t_philo *philo)
{
    int	i;

    i = 0;
    while (i < philo->nb_philo)
    {
        pthread_mutex_destroy(&philo->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&philo->print);
}

void	destroy_thread(t_philo *philo)
{
    int	i;

    i = 0;
    while (i < philo->nb_philo)
    {
        pthread_join(philo->thread[i], NULL);
        i++;
    }
    free(philo->thread);
}

void	destroy_struct(t_philo *philo)
{
    free(philo->forks);
    free(philo);
}

int	check_arg(int argc, char **argv)
{
    int	i;
    int	j;

    i = 1;
    while (i < argc)
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

t_philo	*init_philo(int argc, char **argv)
{
    t_philo	*philo;

    philo = malloc(sizeof(t_philo));
    if (!philo)
        return (NULL);
    philo->nb_philo = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    philo->nb_eat = -1;
    if (argc == 6)
        philo->nb_eat = ft_atoi(argv[5]);
    philo->start = get_time();
    return (philo);
}

int	main(int argc, char **argv)
{
    t_philo	*philo;

    if (argc < 5 || argc > 6)
        return (1);
    if (check_arg(argc, argv))
        return (1);
    philo = init_philo(argc, argv);
    if (!philo)
        return (1);
    if (create_mutex(philo))
        return (1);
    if (create_thread(philo))
        return (1);
    destroy_thread(philo);
    destroy_mutex(philo);
    destroy_struct(philo);
    return (0);
}
//