/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:33:17 by eenassir          #+#    #+#             */
/*   Updated: 2024/09/23 14:30:09 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "philo.h"

typedef struct s_init
{
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		time;
	pthread_mutex_t		lock;
	pthread_mutex_t		*forks;
	long				start;
	int					is_died;
	int					num_philo;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					n_meals_must_eat;
	int					stop_simul;
}	t_init;

typedef struct s_list
{
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_init				*init;
	long				run;
	int					id;
	int					num_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					n_meals_must_eat;
	int					times_eaten;
	long				last_meal;
}	t_list;

#endif