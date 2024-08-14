/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:24:34 by eenassir          #+#    #+#             */
/*   Updated: 2024/08/13 15:39:25 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_list
{
	int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int times_must_eat;
    int times_eaten;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long long last_meal_time;
	struct s_list *next;
} t_list;

int ft_strlen (char *s);
t_list *ft_lst_new(void);
void ft_free_lst(t_list **lst);
int ft_atoi(char *s);

#endif