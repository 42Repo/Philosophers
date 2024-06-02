/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:54:24 by asuc              #+#    #+#             */
/*   Updated: 2024/06/02 18:09:57 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_all(t_data *data, char *str, pthread_t *monitor_thread,
		int last_thread)
{
	int	i;

	if (monitor_thread)
		pthread_join(*monitor_thread, NULL);
	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	i = 0;
	while (i <= last_thread)
		pthread_join(data->philos[i++].thread, NULL);
	free(data->fork);
	free(data->philos);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	if (init_all(&data, argv))
		return (1);
	if (started_threads(&data))
		return (1);
	free_all(&data, NULL, NULL, -1);
	return (0);
}
