/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:55:46 by eenassir          #+#    #+#             */
/*   Updated: 2024/10/05 22:24:06 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <semaphore.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

typedef struct s_data
{
	sem_t *fork;
	sem_t *sem_w;
	sem_t *sem_time;
	sem_t *sem_death;
	int 	num;
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	long long	run_time;
	int		stop_sim;
} t_data;


typedef struct s_list
{
	int 	id;
	int 	meals_must_eat;
	long long last_meal_time;
	pthread_t lock;
	pid_t	pid;
	t_data *data;
} t_list;

int ft_atoi(char *s);
int ft_strlen (char *s);

#endif