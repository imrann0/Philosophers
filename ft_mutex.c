/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:24:49 by albozkur          #+#    #+#             */
/*   Updated: 2024/04/17 12:05:52 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int	free_philo(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&table->philo[i].mutex);
		i++;
	}
	free_mutex(table->philo_count, table->forks);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->mutex_check);
	free(table->forks);
	free(table->philo);
	printf("Philo Mutex ");
	return (1);
}

void	free_mutex(int count, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
}

pthread_mutex_t	*forks_mutex(int count)
{
	int				i;
	pthread_mutex_t	*mutex;

	mutex = (pthread_mutex_t *)malloc(count * sizeof(pthread_mutex_t));
	i = 0;
	if (mutex == NULL)
		return (NULL);
	while (i < count)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
		{
			free_mutex(i, mutex);
			pthread_mutex_destroy(mutex);
			printf("Forks Mutex ");
			return (NULL);
		}
		i++;
	}
	return (mutex);
}
