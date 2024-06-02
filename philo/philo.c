/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:59:58 by asuc              #+#    #+#             */
/*   Updated: 2024/06/02 19:28:50 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	print_message("\033[1;33mis thinking\033[0m", philo, philo->id);
}

void	dream(t_philo *philo)
{
	print_message("\033[1;36mis sleeping\033[0m", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	print_message("\033[1;32mhas taken a fork\033[0m", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	print_message("\033[1;32mhas taken a fork\033[0m", philo, philo->id);
	philo->eating = 1;
	print_message("\033[1;34mis eating\033[0m", philo, philo->id);
	
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	started_threads(t_data *data)
{
	pthread_t	monitoring;
	int			i;

	i = 0;
	if (pthread_create(&monitoring, NULL, &monitor, (void *)data->philos) != 0)
		free_all(data, "Error: failed to create monitoring thread", NULL, -1);
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				(void *)&data->philos[i]) != 0)
			free_all(data, "Error", &monitoring, i - 1);
		i++;
	}
	i = 0;
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
