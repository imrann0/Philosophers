/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_preparation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:11:15 by albozkur          #+#    #+#             */
/*   Updated: 2024/04/25 17:29:26 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philosophers.h"

void	philo_wait(t_table *table, int count)
{
	if (table->philo_count > 1)
		pthread_join(table->asta, NULL);
	while (count >= 0)
	{
		pthread_join(table->philo[count].thread, NULL);
		count--;
	}
}

int	created_thread(pthread_t *thread, void *arg)
{
	if (pthread_create(thread, NULL, &philo, arg) != 0)
		return (1);
	return (0);
}

int	created_table(t_table *table)
{
	int	i;

	table->start_time = current_time();
	i = 0;
	while (i < table->philo_count)
	{
		table->philo[i].id = i;
		table->philo[i].time_to_meal = table->start_time;
		table->philo[i].table = table;
		table->philo[i].meals_count = 0;
		table->philo[i].right_fork = i;
		table->philo[i].left_fork = i - 1;
		if (i == 0)
			table->philo->left_fork = table->philo_count - 1;
		if (pthread_mutex_init(&table->philo[i].mutex, NULL) != 0)
			return (free_philo(table, i));
		if (created_thread(&table->philo[i].thread, &table->philo[i]))
			return (free_philo(table, i));
		i++;
	}
	if (table->philo_count > 1)
		if (pthread_create(&table->asta, NULL, &asta, table))
			return (free_philo(table, i));
	philo_wait(table, i - 1);
	return (0);
}

int	crated_mutex(t_table *table)
{
	table->forks = forks_mutex(table->philo_count);
	if (!table->forks)
		return (1);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		free_mutex(table->philo_count, table->forks);
		free(table->forks);
		return (1);
	}
	if (pthread_mutex_init(&table->mutex_check, NULL) != 0)
	{
		free_mutex(table->philo_count, table->forks);
		free(table->forks);
		pthread_mutex_destroy(&table->print_mutex);
		return (1);
	}
	return (0);
}

int	beginning_philo(t_table *table, char **av)
{
	table->philo_count = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->stop_philo = 0;
	table->must_eat = -1;
	if (av[5])
		table->must_eat = ft_atoi(av[5]);
	if (crated_mutex(table))
		return (1);
	table->philo = (t_philo *)malloc(table->philo_count * sizeof(t_philo));
	if (!table->philo)
	{
		free_mutex(table->philo_count, table->forks);
		free(table->forks);
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->mutex_check);
		return (1);
	}
	if (created_table(table))
		return (1);
	return (0);
}
