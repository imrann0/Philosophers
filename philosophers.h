/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albozkur <albozkur@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:13:56 by albozkur          #+#    #+#             */
/*   Updated: 2024/04/25 15:13:19 by albozkur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINKING "is thinking"
# define DEAD "DİED"

# include <pthread.h>
# include <stdio.h>

typedef struct s_philo
{
	int				id;
	int				meals_count;
	int				left_fork;
	int				right_fork;
	long long		time_to_meal;
	pthread_mutex_t	mutex;
	struct s_table	*table;
	pthread_t		thread;
}		t_philo;

typedef struct s_table
{
	int				philo_count;
	int				must_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				stop_philo;
	long long		start_time;
	pthread_mutex_t	mutex_check;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
	pthread_t		asta;
	pthread_mutex_t	*forks;
}	t_table;

//main.c
void			update_simulation_status_check(t_table *table, int status);
int				simulation_status_check(t_table *table);
int				meal_control(t_philo *philo);

//dinner.c
void			*philo_eat_sleep(t_philo *philo);
void			*think(t_philo *philo, int status);
void			*philo(void *arg);

//dinner_preparation.c
int				created_thread(pthread_t *thread, void *arg);
int				created_table(t_table *table);
int				beginning_philo(t_table *table, char **av);

int				check_av(int ar, char **av);
long			ft_atoi(char *num);

//mutex.c
pthread_mutex_t	*forks_mutex(int count);
void			free_mutex(int count, pthread_mutex_t *mutex);
int				free_philo(t_table *table, int count);

//time.c
long long		current_time(void);
void			start_wait_time(long long time);
void			wait_time(t_table *table, long long time);

//print.c
void			log_print(t_philo *philo, char *status, int mod);
//asta.c
void			*asta(void *arg);
#endif
