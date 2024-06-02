/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:36:42 by asuc              #+#    #+#             */
/*   Updated: 2024/06/02 18:42:23 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf("Usage: %s number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
				argv[0]));
	while (i < argc)
	{
		if (!check_number(argv[i]))
			return (printf("Not number argument in: %s\n", argv[i]));
		i++;
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoll(argv[i]) <= 0)
			return (printf("Invalid argument in: %s\n", argv[i]));
		i++;
	}
	return (0);
}
