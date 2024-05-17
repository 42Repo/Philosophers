/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:54:24 by asuc              #+#    #+#             */
/*   Updated: 2024/05/14 00:12:56 by asuc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	(void)data;
	(void)i;

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
	free_all(&data);
	return (0);
}