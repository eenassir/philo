/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:24:34 by eenassir          #+#    #+#             */
/*   Updated: 2024/08/27 20:51:53 by eenassir         ###   ########.fr       */
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

typedef struct s_init
{
    int num_philo;
    int time_to_die;
    int time_to_sleep;
    int time_to_eat;
    int meals_must_eat;
    long long start;
} t_init;

typedef struct s_list {
    int id;                              // Philosopher's ID
    int num_philo;
    int flag;                       // Total number of philosophers
    long long time_to_die;               // Time (in ms) a philosopher can survive without eating
    long long time_to_eat;               // Time (in ms) a philosopher spends eating
    long long time_to_sleep;             // Time (in ms) a philosopher spends sleeping
    int times_must_eat;                  // Number of times a philosopher must eat (optional)
    int times_eaten;                     // Number of times the philosopher has eaten
    long long last_meal_time;            // Timestamp of the last time the philosopher ate
    long long start;                     // Start time of the simulation
    pthread_mutex_t *left_fork;          // Pointer to the left fork (mutex)
    pthread_mutex_t *right_fork;         // Pointer to the right fork (mutex)
    pthread_mutex_t *output_lock;        // Mutex for synchronizing output (printing)
    pthread_mutex_t meal_time_lock;      // Mutex for protecting access to last_meal_time
    pthread_mutex_t sim_running_lock;    // Mutex for protecting access to simulation_running
    int *simulation_running;
    int i;             // Flag to indicate if the simulation is running
} t_list;

int ft_strlen (char *s);
t_list *ft_lst_new(void);
void ft_free_lst(t_list **lst);
int ft_atoi(char *s);
int ft_strcmp(char *s1, char *s2);

#endif