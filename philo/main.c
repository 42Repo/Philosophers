/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:54:24 by asuc              #+#    #+#             */
/*   Updated: 2024/06/05 16:37:16 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_destroy(&data->wait_lock);
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

void	*single_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->l_fork);
	print_message("\033[1;32mhas taken a fork\033[0m", philo, philo->id);
	ft_usleep(philo->time_to_die);
	pthread_mutex_unlock(philo->l_fork);
	print_message("\033[1;31mdied\033[0m", philo, philo->id);
	pthread_mutex_lock(philo->dead_lock);
	*philo->dead = 1;
	pthread_mutex_unlock(philo->dead_lock);
	return (NULL);
}

void	start_philo(t_data *data, pthread_t *monitoring)
{
	int	i;

	i = 0;
	while (i < data->philos[0].num_of_philos
		&& data->philos[0].num_of_philos > 1)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				(void *)&data->philos[i]) != 0)
		{
			pthread_mutex_unlock(&data->wait_lock);
			free_all(data, "Error", monitoring, i - 1);
		}
		i++;
	}
}

int	started_threads(t_data *data)
{
	pthread_t	monitoring;
	int			i;

	i = 0;
	if (pthread_create(&monitoring, NULL, &monitor, (void *)data->philos) != 0)
		free_all(data, "Error: failed to create monitoring thread", NULL, -1);
	pthread_mutex_lock(&data->wait_lock);
	start_philo(data, &monitoring);
	if (data->philos[0].num_of_philos == 1)
	{
		single_philo(&data->philos[0]);
		pthread_mutex_unlock(&data->wait_lock);
		free_all(data, NULL, &monitoring, -1);
	}
	i = 0;
	pthread_mutex_unlock(&data->wait_lock);
	if (pthread_join(monitoring, NULL))
		free_all(data, "Error", NULL, data->philos[0].num_of_philos - 1);
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			free_all(data, "Error", NULL, data->philos[0].num_of_philos - 1);
		i++;
	}
	return (0);
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
