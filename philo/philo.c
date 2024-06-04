/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:59:58 by asuc              #+#    #+#             */
/*   Updated: 2024/06/04 21:45:48 by asuc             ###   ########.fr       */
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

void	lock_order(t_philo *philo, pthread_mutex_t **fork1,
	pthread_mutex_t **fork2)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(*fork2);
	else
		pthread_mutex_lock(*fork1);
}

void	eat(t_philo *philo)
{
	lock_order(philo, &philo->r_fork, &philo->l_fork);
	print_message("\033[1;32mhas taken a fork\033[0m", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	lock_order(philo, &philo->l_fork, &philo->r_fork);
	print_message("\033[1;32mhas taken a fork\033[0m", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	print_message("\033[1;34mis eating\033[0m", philo, philo->id);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	pthread_mutex_lock(philo->wait_lock);
	pthread_mutex_unlock(philo->wait_lock);
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
