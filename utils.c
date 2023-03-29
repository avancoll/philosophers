/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:40:20 by avancoll          #+#    #+#             */
/*   Updated: 2023/03/29 15:40:36 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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