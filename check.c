/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:58:29 by albozkur          #+#    #+#             */
/*   Updated: 2024/04/25 16:57:11 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_simulation_status_check(t_table *table, int status)
{
	pthread_mutex_lock(&table->mutex_check);
	table->stop_philo = status;
	pthread_mutex_unlock(&table->mutex_check);
}

int	simulation_status_check(t_table *table)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&table->mutex_check);
	if (table->stop_philo == 1)
		status = 1;
	pthread_mutex_unlock(&table->mutex_check);
	return (status);
}

int	meal_control(t_philo *philo)
{
	if (philo->table->must_eat == -1)
		return (1);
	return (philo->meals_count < philo->table->must_eat);
}
