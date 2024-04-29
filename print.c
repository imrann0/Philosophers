/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:00:54 by albozkur          #+#    #+#             */
/*   Updated: 2024/04/17 12:06:00 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_print(t_philo *philo, char *status, int mod)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (simulation_status_check(philo->table) == 1 && mod == 0)
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	printf("%lld ", current_time() - philo->table->start_time);
	printf("%d ", philo->id + 1);
	printf("%s\n", status);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
