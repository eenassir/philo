/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:04:57 by eenassir          #+#    #+#             */
/*   Updated: 2024/09/15 11:41:19 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"


void ft_usleep(int time)
{
	long start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(50);
}
void print_msg(char *s, t_list *philo)
{
    // if (philo->init->stop_simul != 1)
    // {
        pthread_mutex_lock(&philo->init->write_mutex); // kola wa7d
        printf ("%d %d %s\n", (int)(get_current_time() - philo->run), philo->id, s);
        pthread_mutex_unlock(&philo->init->write_mutex);
    // }
}

int meal(t_list *philo)
{
    int i;
    int full;
    
    i = 0;
    full = 0;
    pthread_mutex_lock(&philo->init->time);
    while (i < philo->num_philo)
    {
        if (philo[i].times_must_eat == 0)
        {
            full++;
        }  
        i++;
    }
    if (full == philo->num_philo)
    {
        pthread_mutex_unlock(&philo->init->time);
        return (1);   
    }
    pthread_mutex_unlock(&philo->init->time);
    return (0);
}

void *ft_monitor(void *arg)
{
    t_list *philo = (t_list *)arg;
    // int stop_simul;
    int i;

    while (1)
    {
        // if (meal(philo))
        //     return (NULL);
        i = 0;
        while (i < philo->init->num_philo)
        {
            pthread_mutex_lock(&philo->init->time);
            if (((int)(get_current_time() - philo->run) - philo[i].last_meal_time) >= (int)philo->time_to_die)
            {
                pthread_mutex_lock(&philo->init->write_mutex);
				philo->init->stop_simul = 1;
                pthread_mutex_unlock(&philo->init->time);
                printf("%lld %d has died\n", (get_current_time() - philo[i].run), philo[i].id);
                return NULL;
                // pthread_mutex_unlock(&philo->init->lock_stop);
                
                // pthread_mutex_lock(&philo->init->write_mutex);
            }
             pthread_mutex_unlock(&philo->init->time);
            i++;
        }
        // pthread_mutex_lock(&philo->init->lock_stop);
        // if (philo->init->stop_simul == 1)
        // {
        //     pthread_mutex_unlock(&philo->init->lock_stop);
        //     break  ;
        // }
        // pthread_mutex_unlock(&philo->init->lock_stop);
    }
    // if (philo->init->stop_simul == 1)
    //     exit(0);
	return (NULL);
}

void *life_cycle(void *arg)
{
    int         stop_simul;
    t_list *philo = (t_list *)arg;
    int i;


    if (philo->id % 2 == 0)
        usleep(philo->time_to_eat);
        
    i = 0;
    while (1)
    {
        if (philo->times_must_eat <= 0)
        {
            break ;
        }
        pthread_mutex_lock(&philo->init->lock_stop);
        stop_simul = philo->init->stop_simul;
        pthread_mutex_unlock(&philo->init->lock_stop);
        pthread_mutex_lock(philo->left_fork);
        
        print_msg("has taken a fork", philo);
        pthread_mutex_lock(philo->right_fork);
        
        print_msg("has taken a fork", philo);
        print_msg("is eating", philo);
        ft_usleep(philo->time_to_eat);
        pthread_mutex_lock(&philo->init->time);
        philo->last_meal_time = get_current_time() - philo->run;
        philo->times_must_eat--;
        pthread_mutex_unlock(&philo->init->time);
        
        pthread_mutex_unlock(philo->right_fork);
        
        pthread_mutex_unlock(philo->left_fork);
        print_msg("is sleeping", philo);
        ft_usleep(philo->time_to_sleep);
        print_msg("is thinking", philo);
    }
    return (NULL);
}

void *ft_loop(t_init *init, t_list *philo)
{
    pthread_mutex_t *forks;
    int i;

    i = 0;
    forks = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * init->num_philo);
    if (!forks)
        return NULL;
    while (i < init->num_philo)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < init->num_philo)
    {
        philo[i].init = init;
        philo[i].id = i + 1;
        philo[i].num_philo = init->num_philo;
        philo[i].time_to_die = init->time_to_die;
        philo[i].time_to_sleep = init->time_to_sleep;
        philo[i].time_to_eat = init->time_to_eat;
        philo[i].times_must_eat = init->meals_must_eat;
        philo[i].last_meal_time = init->start;
        philo[i].right_fork = &forks[i];
        philo[i].left_fork = &forks[(i + 1) % init->num_philo];
        i++;
    }
    return (NULL);
}

int ft_philo(int ac, char **av)
{
    pthread_t monitor;
    pthread_t *th;
    int i;
    int n;

    n = ft_atoi(av[1]);
    if (n == -1)
        return (-1);
    th = (pthread_t *)malloc(sizeof (pthread_t) * n);
    if (!th)
        return -1;
    t_list *philo = malloc(sizeof(t_list) * n);
    t_init *init = malloc(sizeof(t_init));
    init->num_philo = ft_atoi(av[1]);
    init->time_to_die = ft_atoi(av[2]);
    init->time_to_eat = ft_atoi(av[3]);
    init->time_to_sleep = ft_atoi(av[4]);
    if (init->num_philo == -1 || init->time_to_die == -1 \
        || init->time_to_sleep == -1 || init->time_to_eat == -1)
        return (-1);
    if (ac == 6)
    {
        init->meals_must_eat = ft_atoi(av[5]);
        if (init->meals_must_eat == -1)
            return (-1);
    }
    else
        init->meals_must_eat = -1;
    init->stop_simul = 0;
    pthread_mutex_init(&init->write_mutex, NULL);
    pthread_mutex_init(&init->time, NULL);
    pthread_mutex_init(&init->lock_stop, NULL);
    ft_loop(init, philo);
    i = 0;
    init->start = get_current_time();
    while (i < init->num_philo)
    {
        philo[i].run = init->start;
        i++;
    }
    i = 0;
    while (i < init->num_philo)
    {
        pthread_create(&th[i], NULL, life_cycle, &philo[i]);
        i++;
    }
    ft_monitor(philo);
    i = 0;
    while (i< init->num_philo)
    {
        pthread_detach(th[i]);
        i++;
    }
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 5 && ac != 6)
    {
        printf("The number of arguments is not enough or exceeds the expected number!\n");
        return (1);
    }
    ft_philo(ac, av);
    return (0);
}
