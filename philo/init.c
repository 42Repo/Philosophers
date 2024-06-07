/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:16:47 by asuc              #+#    #+#             */
/*   Updated: 2024/06/07 17:47:27 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char *argv[])
{
	data->philos = malloc(sizeof(t_philo) * ft_atoll(argv[1]));
	if (!data->philos)
		return (print_error("Error: malloc failed\n"));
	data->dead_flag = 0;
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->wait_lock, NULL);
	return (0);
}

void	init_input(t_philo *philo, char *argv[])
{
	philo->num_of_philos = ft_atoll(argv[1]);
	philo->time_to_die = ft_atoll(argv[2]);
	philo->time_to_eat = ft_atoll(argv[3]);
	philo->time_to_sleep = ft_atoll(argv[4]);
	philo->num_times_to_eat = -1;
	if (argv[5])
		philo->num_times_to_eat = ft_atoll(argv[5]);
}

int	init_philos(t_data *data, pthread_mutex_t **fork, char *argv[])
{
	int	i;

	i = 0;
	while (i < ft_atoll(argv[1]))
	{
		init_input(&data->philos[i], argv);
		data->philos[i].id = i;
		data->philos[i].eating = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_current_time();
		data->philos[i].start_time = get_current_time();
		data->philos[i].dead = &data->dead_flag;
		data->philos[i].write_lock = &data->write_lock;
		data->philos[i].dead_lock = &data->dead_lock;
		data->philos[i].meal_lock = &data->meal_lock;
		data->philos[i].wait_lock = &data->wait_lock;
		data->philos[i].r_fork = &(*fork)[i];
		if (i == 0)
			data->philos[i].l_fork = &(*fork)[ft_atoll(argv[1]) - 1];
		else
			data->philos[i].l_fork = &(*fork)[i - 1];
		i++;
	}
	return (0);
}

int	init_forks(pthread_mutex_t **forks, int num_of_philos)
{
	int	i;

	i = 0;
	(*forks) = malloc(sizeof(pthread_mutex_t) * num_of_philos);
	if (!(*forks))
		return (1);
	while (i < num_of_philos)
	{
		pthread_mutex_init(&((*forks)[i]), NULL);
		i++;
	}
	return (0);
}

int	init_all(t_data *data, char *argv[])
{
	pthread_mutex_t	*forks;

	forks = NULL;
	if (init_data(data, argv))
		return (1);
	if (init_forks(&forks, ft_atoll(argv[1])))
		return (1);
	if (init_philos(data, &forks, argv))
		return (1);
	data->fork = forks;
	return (0);
}
