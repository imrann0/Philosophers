/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:58:13 by albozkur          #+#    #+#             */
/*   Updated: 2024/04/25 15:14:29 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

int	death_control(t_table *table, t_philo *philo)
{
	long long	time;

	time = current_time();
	if ((time - philo->time_to_meal) >= table->time_to_die)
	{
		update_simulation_status_check(table, 1);
		log_print(philo, DEAD, 1);
		pthread_mutex_unlock(&philo->mutex);
		return (1);
	}
	return (0);
}

int	astra_control(t_table *table)
{
	int	i;
	int	mod;

	i = 0;
	mod = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philo[i].mutex);
		if (death_control(table, &table->philo[i]))
			return (1);
		if (table->must_eat != -1)
		{
			if (table->philo[i].meals_count < table->must_eat)
				mod = 1;
		}
		pthread_mutex_unlock(&table->philo[i].mutex);
		i++;
	}
	if (mod == 0 && table->must_eat != -1)
		return (update_simulation_status_check(table, 1), 1);
	return (0);
}

void	*asta(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (astra_control(table) == 1)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
