/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:21:11 by asuc              #+#    #+#             */
/*   Updated: 2024/06/07 17:48:46 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - s2[i]);
}

int	ft_isdigit(int c)
{
	if (!c)
		return (0);
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_isnamespace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	print_error(char *str)
{
	if (!str)
		write(2, "Error\n", 6);
	else
		write(2, str, ft_strlen(str));
	return (1);
}
