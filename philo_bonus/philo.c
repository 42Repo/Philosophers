/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:45:17 by asuc              #+#    #+#             */
/*   Updated: 2024/02/11 12:08:54 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	// t_philosopher	*philosophers;
	// t_table			table;
	// int				i;

	(void)argc;
	(void)argv;
	if (argc != 5 && argc != 6)
		return (ft_error("Wrong number of arguments\n"));
	// if (ft_init_table(&table, argc, argv))
	// 	return (ft_error("Error while initializing table\n"));
	// if (ft_init_philosophers(&philosophers, &table))
	// 	return (ft_error("Error while initializing philosophers\n"));
	// i = 0;
	// while (i < table.number_of_philosophers)
	// {
	// 	if (pthread_create(&philosophers[i].thread, NULL, ft_philosopher, &philosophers[i]))
	// 		return (ft_error("Error while creating philosopher thread\n"));
	// 	i++;
	// }
	// i = 0;
	// while (i < table.number_of_philosophers)
	// {
	// 	if (pthread_join(philosophers[i].thread, NULL))
	// 		return (ft_error("Error while joining philosopher thread\n"));
	// 	i++;
	// }
	// ft_free_table(&table);
	// ft_free_philosophers(philosophers, table.number_of_philosophers);
	return (0);
}
