/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:52:37 by albozkur          #+#    #+#             */
/*   Updated: 2024/04/24 13:27:45 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philosophers.h"
#include <unistd.h>

void	ft_free(t_table *table)
{
	free_mutex(table->philo_count, table->forks);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->mutex_check);
	free(table->forks);
	free(table->philo);
}

int	main(int ar, char **av)
{
	t_table	table;

	if (check_av(ar, av))
		return (printf("Invalid Argument Input\n"), 1);
	if (beginning_philo(&table, av))
		return (printf("Error\n"), 1);
	ft_free(&table);
	return (0);
}
