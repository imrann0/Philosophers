/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:59:21 by albozkur          #+#    #+#             */
/*   Updated: 2024/04/29 14:31:55 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

void	*philo_eat_sleep(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	log_print(philo, FORK, 0);
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	log_print(philo, FORK, 0);
	log_print(philo, EAT, 0);
	pthread_mutex_lock(&philo->mutex);
	philo->time_to_meal = current_time();
	pthread_mutex_unlock(&philo->mutex);
	wait_time(philo->table, philo->table->time_to_eat);
	if (simulation_status_check(table) == 0)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->mutex);
	}
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
	log_print(philo, SLEEP, 0);
	wait_time(philo->table, philo->table->time_to_sleep);
	return (NULL);
}

void	*think(t_philo *philo, int status)
{
	long long	time;
	int			meal_time;
	int			die_time;
	int			eat_time;

	die_time = philo->table->time_to_die;
	meal_time = current_time() - philo->time_to_meal;
	eat_time = philo->table->time_to_eat;
	time = (die_time - meal_time - eat_time) / 2;
	if (time < 0)
		time = 1;
	else if (time == 0 && status == 1)
		time = 1;
	else if (time > 600)
		time = 200;
	if (status == 1)
		log_print(philo, THINKING, 0);
	wait_time(philo->table, time);
	return (NULL);
}

void	*one(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	log_print(philo, FORK, 0);
	wait_time(philo->table, philo->table->time_to_die);
	log_print(philo, DEAD, 0);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	return (NULL);
}

void	*philo(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	if (!arg)
		return (NULL);
	philo = (t_philo *) arg;
	table = philo->table;
	start_wait_time(table->start_time);
	if (table->philo_count == 1)
		return (one(philo));
	else if (philo->id % 2)
		think(philo, 0);
	while (simulation_status_check(table) == 0 && meal_control(philo))
	{
		philo_eat_sleep(philo);
		think(philo, 1);
	}
	return (NULL);
}
