/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:41:07 by asuc              #+#    #+#             */
/*   Updated: 2024/06/04 18:10:59 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*wait_lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	wait_lock;
	pthread_mutex_t	*fork;
	t_philo			*philos;
}					t_data;

int					init_all(t_data *data, char *argv[]);
int					check_args(int argc, char *argv[]);
long long			ft_atoll(const char *str);
void				*philo_routine(void *pointer);
void				*monitor(void *pointer);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
int					dead_loop(t_philo *philo);
void				print_message(char *str, t_philo *philo, int id);
void				free_all(t_data *data, char *str, pthread_t *monitor_thread,
						int last_thread);
#endif