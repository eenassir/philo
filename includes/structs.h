/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:33:17 by eenassir          #+#    #+#             */
/*   Updated: 2024/09/08 11:46:35 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "philo.h"

typedef struct s_init
{
    long start;
    int is_died;
    int num_philo;
    int time_to_die;
    int time_to_sleep;
    int time_to_eat;
    int meals_must_eat;
    pthread_mutex_t write_mutex;
} t_init;

typedef struct s_list {
    long run;
    int  id;                              // Philosopher's ID
    int num_philo;
    int flag;
    int stop_simul;                    
    long time_to_die;
    long time_to_eat;  
    long time_to_sleep;
    int times_must_eat;     
    int times_eaten;                   
    long last_meal_time;          
    pthread_mutex_t *left_fork;        
    pthread_mutex_t *right_fork;       
    pthread_mutex_t *output_lock;      
    pthread_mutex_t meal_time_lock;    
    pthread_mutex_t sim_running_lock;  
    int *simulation_running;
    t_init *init;
} t_list;

#endif