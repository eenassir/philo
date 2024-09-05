/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:04:57 by eenassir          #+#    #+#             */
/*   Updated: 2024/09/05 15:35:45 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// void *ft_monitor(void *arg)
// {
// 	t_list *philo;

// 	philo = (t_list *)arg;
// 	while (1)
// 	{
// 		int i;
// 		i = 0;
// 		while (i < philo->num_philo)
// 		{
// 			if (get_current_time() - philo[i].last_meal_time >= philo[i].time_to_sleep)
// 			{
// 				printf ("%lld %d *******has died*****\n", get_current_time() -
// 					philo->init->start, philo[i].id);
// 				return (NULL);
// 			}
// 			i++;
// 		}
// 		usleep(100);
// 	}
// }

// void *life_cycle(void *arg)
// {
// 	t_list *philo;
// 	pthread_mutex_t o;

// 	philo = (t_list *)arg;
// 	pthread_mutex_init(&o, NULL);
// 		if (philo->id % 2 == 2)
// 			usleep (philo->time_to_eat * 1000);
// 	while (1)
// 	{
// 		printf ("%lld %d is thinking\n", get_current_time() - philo->start, philo->id);
// 		pthread_mutex_lock(philo->left_fork);
// 		printf ("%lld %d has take a fork1\n", get_current_time() - philo->start, philo->id);
// 		if (philo->num_philo == 1)
// 		{
// 			usleep (philo->time_to_die * 1000);
// 			printf ("%lld %d is died\n", get_current_time() - philo->start, philo->id);
// 			pthread_mutex_unlock(philo->left_fork);
// 			break ;
// 		}
// 		pthread_mutex_lock(philo->right_fork);
// 		printf ("%lld %d has take a fork2\n", get_current_time() - philo->start, philo->id);
// 		printf ("%lld %d is eating\n", get_current_time() - philo->start, philo->id);
// 		philo->last_meal_time = get_current_time();
// 		usleep(philo->time_to_eat * 1000);
// 		philo->times_must_eat--;
// 		if (philo->times_must_eat == 0)
// 			break ;
// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);
// 		printf ("%lld %d is sleeping\n", get_current_time() - philo->start, philo->id);
// 		usleep (philo->time_to_sleep * 1000);
// 	}
// 	return (NULL);
// }

// void ft_loop(t_init *init)
// {
// 	pthread_t monitor;
// 	pthread_t th[init->num_philo];
// 	t_list philo[init->num_philo];
// 	pthread_mutex_t forks[init->num_philo];
// 	int i;

// 	i = 0;
// 	while (i < init->num_philo)
// 		pthread_mutex_init(&forks[i++], NULL);
// 	i = 0;
// 	init->start = get_current_time();
// 	while (i < init->num_philo)
// 	{
// 		philo[i].id = i + 1;
// 		philo[i].num_philo = init->num_philo;
// 		philo[i].time_to_die = init->time_to_die;
// 		philo[i].time_to_sleep = init->time_to_sleep;
// 		philo[i].time_to_eat = init->time_to_eat;
// 		philo[i].times_must_eat = init->meals_must_eat;
// 		philo[i].i = init->meals_must_eat;
// 		philo[i].right_fork = &forks[(i + 1) % init->num_philo];
// 		philo[i].left_fork = &forks[i];
// 		philo[i].last_meal_time = 0;
// 		philo[i].times_eaten = 0;
// 		philo[i].start = init->start;
// 		pthread_create (&th[i], NULL, life_cycle, &philo[i]);
// 		i++;
// 	}
// 	pthread_create (&monitor, NULL, ft_monitor, NULL);
	 
// 	i = 0;
// 	while (i < philo->num_philo)
// 	{
// 		pthread_join(th[i], NULL);
// 		i++;
// 	}
// 	pthread_join(monitor, NULL);
// }

// void ft_philo(int ac, char **av)
// {
// 	t_init init;
// 	int i;
	
// 	i = 0;
// 	init.num_philo = ft_atoi(av[1]);
// 	init.time_to_die = ft_atoi(av[2]);
// 	init.time_to_sleep = ft_atoi(av[3]);
// 	init.time_to_eat = ft_atoi(av[4]);
// 	if (ac == 6)
// 		init.meals_must_eat = ft_atoi(av[5]);
// 	else
// 		init.meals_must_eat = -1;
// 	ft_loop(&init);
// }



// int main(int ac, char **av)
// {
// 	t_list philo;
// 	int i = 0;

// 	if (ac != 5 && ac != 6)
// 	{
// 		printf ("the nbr of arguments isn't enough or more than the expected!!");
// 		return (1);
// 	}
// 	ft_philo(ac, av);
// }

void ft_usleep(int time)
{
	long long start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(100);
}
void *ft_monitor(void *arg)
{
    t_list *philo = (t_list *)arg;
    int i;

    while (1)
    {
        i = 0;
        while (i < philo->num_philo)
        {
            if ((get_current_time() - philo[i].last_meal_time) >= philo[i].time_to_die)
            {
                printf("%lld %d *******has died*****\n", (get_current_time() - philo[i].start), philo[i].id);
				philo->stop_simul = 1;
                break ;
            }
            i++;
        }
        if (philo->stop_simul == 1)
            break ;
		usleep(100);
    }
	return (NULL);
}

void *life_cycle(void *arg)
{
    t_list *philo = (t_list *)arg;
    pthread_mutex_t o;

    pthread_mutex_init(&o, NULL);
    if (philo->id % 2 == 0)
         ft_usleep(philo->time_to_eat);
    while (1)
    {
		printf("stp = %d\n", philo->stop_simul);
		if (philo->stop_simul == 1)
			return (NULL);
        printf("%lld %d is thinking\n", get_current_time() - philo->start, philo->id);
        pthread_mutex_lock(philo->left_fork);
        printf("%lld %d has taken fork 1\n", get_current_time() - philo->start, philo->id);
        if (philo->num_philo == 1)
        {
            ft_usleep(philo->time_to_die);
            printf("%lld %d has died\n", get_current_time() - philo->start, philo->id);
            pthread_mutex_unlock(philo->left_fork);
            break;
        }
        pthread_mutex_lock(philo->right_fork);
        printf("%lld %d has taken fork 2\n", get_current_time() - philo->start, philo->id);
        printf("%lld %d is eating\n", get_current_time() - philo->start, philo->id);

        philo->last_meal_time = get_current_time();
        ft_usleep(philo->time_to_eat);
        philo->times_must_eat--;
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        if (philo->times_must_eat == 0)
            break;

        printf("%lld %d is sleeping\n", get_current_time() - philo->start, philo->id);
        ft_usleep(philo->time_to_sleep);
    }
    return (NULL);
}

void ft_loop(t_init *init)
{
    pthread_t monitor;
    pthread_t th[init->num_philo];
    t_list philo[init->num_philo];
    pthread_mutex_t forks[init->num_philo];
    int i = 0;

    // Initialize mutexes for forks
	philo->stop_simul = 0;
    while (i < init->num_philo)
        pthread_mutex_init(&forks[i++], NULL);

    // Start time
    init->start = get_current_time();

    // Initialize philosophers
    i = 0;
    while (i < init->num_philo)
    {
        philo[i].id = i + 1;
        philo[i].num_philo = init->num_philo;
        philo[i].time_to_die = init->time_to_die;
        philo[i].time_to_sleep = init->time_to_sleep;
        philo[i].time_to_eat = init->time_to_eat;
        philo[i].times_must_eat = init->meals_must_eat;
        philo[i].last_meal_time = init->start; // Set last meal time to the start time
        philo[i].left_fork = &forks[i];
        philo[i].right_fork = &forks[(i + 1) % init->num_philo];
        philo[i].start = init->start;
        pthread_create(&th[i], NULL, life_cycle, &philo[i]);
        i++;
    }

    // Pass the list of philosophers to the monitor

    // Wait for all threads to finish
    pthread_create(&monitor, NULL, ft_monitor, philo);
    i = 0;
    while (i < init->num_philo)
    {
        pthread_join(th[i], NULL);
        i++;
    }
    pthread_join(monitor, NULL);
}

void ft_philo(int ac, char **av)
{
    t_init init;

    init.num_philo = ft_atoi(av[1]);
    init.time_to_die = ft_atoi(av[2]);
    init.time_to_sleep = ft_atoi(av[3]);
    init.time_to_eat = ft_atoi(av[4]);
    if (ac == 6)
        init.meals_must_eat = ft_atoi(av[5]);
    else
        init.meals_must_eat = -1;

    ft_loop(&init);
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
