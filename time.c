/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:51:37 by albozkur          #+#    #+#             */
/*   Updated: 2024/04/29 11:52:58 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "philosophers.h"

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

void	start_wait_time(long long time)
{
	while (current_time() < time)
	{
		usleep(10);
	}
}

void	wait_time(t_table *table, long long time)
{
	long long	mytime;

	mytime = current_time() + time;
	while (current_time() < mytime)
	{
		if (simulation_status_check(table) == 1)
			return ;
		usleep(100);
	}
}
