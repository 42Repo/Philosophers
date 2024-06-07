/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:36:42 by asuc              #+#    #+#             */
/*   Updated: 2024/06/07 18:06:00 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_negative(const char **str)
{
	int	is_negative;

	is_negative = 0;
	if (**str == '-')
	{
		is_negative = 1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (is_negative);
}

int	is_long_long_in_range(const char *str)
{
	int			is_negative;
	const char	*llong_max_str = "9223372036854775807";
	const char	*llong_min_str = "9223372036854775808";
	const char	*compare_str;

	while (ft_isnamespace(*str))
		str++;
	while (*str == '0')
		str++;
	if (*str == '\0')
		return (1);
	is_negative = check_negative(&str);
	if (*str == '\0' || !ft_isdigit(*str))
		return (0);
	if (is_negative)
		compare_str = llong_min_str;
	else
		compare_str = llong_max_str;
	if (ft_strlen(str) > ft_strlen(compare_str))
		return (0);
	if (ft_strlen(str) < ft_strlen(compare_str))
		return (1);
	return (ft_strncmp(str, compare_str, ft_strlen(str)) <= 0);
}

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
	if (is_long_long_in_range(str))
		return (1);
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
			return (printf("Invalid argument in: %s\n", argv[i]));
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
