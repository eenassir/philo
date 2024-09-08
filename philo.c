/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:04:57 by eenassir          #+#    #+#             */
/*   Updated: 2024/09/08 23:17:22 by eenassir         ###   ########.fr       */
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
	long start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(50);
}
void *ft_monitor(void *arg)
{
    t_list *philo = (t_list *)arg;
    t_init  *init;
    int i;
    pthread_mutex_t lock;

    // printf (">%ld<\n", philo->last_meal_time);
    while (1)
    {
        i = 0;
        
        while (i < philo->init->num_philo)
        {
            // printf("[%lld][%ld]\n",get_current_time() - philo->run- philo->last_meal_time,philo->time_to_die);
            if (((int)(get_current_time() - philo[i].run) - philo[i].last_meal_time) >= (int)philo[i].time_to_die)
            {
                // exit(0);
                pthread_mutex_lock(&philo[i].init->write_mutex);
                printf("%lld %d*******************has died***********************************\n", get_current_time() - philo[i].run, philo[i].id);
				philo->stop_simul = 1;
                return (NULL) ;
            }
            i++;
        }
        if (philo->stop_simul == 1)
            return (NULL);
    }
    // if (philo->init->is_died)
    //     exit(0);
	return (NULL);
}

void *life_cycle(void *arg)
{
    
    t_list *philo = (t_list *)arg;
    
    if (philo->stop_simul == 1)
            return (0);
    if (philo->id % 2 == 0)
        ft_usleep(200);
    while (1)
    {
        if (philo->times_must_eat == 0)
            break;
       
        // printf("[%lld][%ld]\n",get_current_time(),philo->init->start);
        // exit(0);
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&philo->init->write_mutex);
        printf("%lld %d has taken fork\n", get_current_time() - philo->run, philo->id);
        pthread_mutex_unlock(&philo->init->write_mutex);       
        // if (philo->num_philo == 1)
        // {
        //     // ft_usleep(philo->time_to_die);
        //     // printf("%lld %d has died\n", get_current_time() - philo->start, philo->id);
        //     pthread_mutex_unlock(philo->left_fork);
        //     break;
        // }        
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&philo->init->write_mutex);
        printf("%lld %d has taken fork\n", get_current_time() - philo->run, philo->id);
        pthread_mutex_unlock(&philo->init->write_mutex);
        
        pthread_mutex_unlock(&philo->init->write_mutex);
        printf("%lld %d is eating\n", get_current_time() - philo->run, philo->id);
        pthread_mutex_unlock(&philo->init->write_mutex);
        ft_usleep(philo->time_to_eat);
        philo->times_must_eat--;
        philo->last_meal_time = get_current_time() - philo->run;
        
        // printf ("<%ld>\n", philo->last_meal_time);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        
        pthread_mutex_lock(&philo->init->write_mutex);
        printf("%lld %d is sleeping\n", get_current_time() - philo->run, philo->id);
        pthread_mutex_unlock(&philo->init->write_mutex);
        ft_usleep(philo->time_to_sleep);
        printf("%lld %d is thinking\n", get_current_time() - philo->run, philo->id);
    }
    pthread_mutex_lock(&philo->init->write_mutex);
    ft_usleep(300);
    pthread_mutex_unlock(&philo->init->write_mutex);
    return (NULL);
}

void ft_loop(t_init *init, t_list *philo)
{
    pthread_mutex_t forks[init[0].num_philo];
    int i;

    i = 0;
    
    while (i < init[0].num_philo)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&init->write_mutex,0);
    i = 0;
    while (i < init[0].num_philo)
    {
        philo[i].init = init;
	    philo[i].stop_simul = 0;
        philo[i].id = i + 1;
        philo[i].num_philo = init->num_philo;
        philo[i].time_to_die = init->time_to_die;
        philo[i].time_to_sleep = init->time_to_sleep;
        philo[i].time_to_eat = init->time_to_eat;
        philo[i].times_must_eat = init->meals_must_eat;
        philo[i].last_meal_time = init->start;
        philo[i].left_fork = &forks[i];
        philo[i].right_fork = &forks[(i + 1) % init->num_philo];
        i++;
    }
}

int ft_philo(int ac, char **av)
{
    pthread_t monitor;
    pthread_t th[ft_atoi(av[1])];
    int i;
    int n;

    n = ft_atoi(av[1]);
    if (n == -1)
        return (-1);
    t_list *philo = malloc(sizeof(t_list) * n);
    t_init *init = malloc(sizeof(t_init));
    init->is_died = 0;
    init->num_philo = ft_atoi(av[1]);
    init->time_to_die = ft_atoi(av[2]);
    init->time_to_sleep = ft_atoi(av[4]);
    init->time_to_eat = ft_atoi(av[3]);
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
    ft_loop(init, philo);
    i = 0;
    init->start = get_current_time();
    while (i < init->num_philo)
    {
        philo[i].run = init->start;
        pthread_create(&th[i], NULL, life_cycle, &philo[i]);
        pthread_detach(th[i]);
        i++;
    }
    i = 0;
    ft_monitor(philo);
    if (philo->stop_simul == 1)
        return (1);
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
