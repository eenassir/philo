/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:04:57 by eenassir          #+#    #+#             */
/*   Updated: 2024/08/27 22:57:24 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_current_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void *life_cycle(void *arg)
{
	t_list *philo;
	pthread_mutex_t o;

	philo = (t_list *)arg;
	pthread_mutex_init(&o, NULL);
	while (1)
	{
		if (philo->id % 2 == 2)
			usleep (philo->time_to_sleep * 1000);
		printf ("%lld %d is thinking\n", get_current_time() - philo->start, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf ("%lld %d has take a fork1\n", get_current_time() - philo->start, philo->id);
		if (philo->num_philo == 1)
		{
			usleep (philo->time_to_die * 1000);
			printf ("%lld %d is died\n", get_current_time() - philo->start, philo->id);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		pthread_mutex_lock(philo->right_fork);
		printf ("%lld %d has take a fork2\n", get_current_time() - philo->start, philo->id);
		printf ("%lld %d is eating\n", get_current_time() - philo->start, philo->id);
		philo->last_meal_time = get_current_time();
		usleep(philo->time_to_eat * 1000);
		philo->times_must_eat--;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf ("%lld %d is sleeping\n", get_current_time() - philo->start, philo->id);
		usleep (philo->time_to_sleep * 1000);
		usleep (1000);
		if (get_current_time() - philo->last_meal_time >= philo->time_to_die)
		{
			printf ("%lld %d has died\n", get_current_time() -philo->start, philo->id);
			return (NULL);
		}
		if (philo->i > 0 && philo->times_must_eat <= 0)
			break ;
	}
	return (NULL);
}

void ft_loop(t_init *init)
{
	pthread_t th[init->num_philo];
	t_list philo[init->num_philo];
	pthread_mutex_t forks[init->num_philo];
	int i;

	i = 0;
	while (i < init->num_philo)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	init->start = get_current_time();
	while (i < init->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].num_philo = init->num_philo;
		philo[i].time_to_die = init->time_to_die;
		philo[i].time_to_sleep = init->time_to_sleep;
		philo[i].time_to_eat = init->time_to_eat;
		philo[i].times_must_eat = init->meals_must_eat;
		philo[i].i = init->meals_must_eat;
		philo[i].right_fork = &forks[(i + 1) % init->num_philo];
		philo[i].left_fork = &forks[i];
		philo[i].last_meal_time = 0;
		philo[i].times_eaten = 0;
		philo[i].start = init->start;
		pthread_create (&th[i], NULL, life_cycle, &philo[i]);
		i++;
	}
	i = 0;
	while (i < init->num_philo)
		pthread_join(th[i++], NULL);
	i = 0;
	while (i < init->num_philo)
		pthread_mutex_destroy(&forks[i++]);
}

void ft_philo(int ac, char **av)
{
	t_init init;
	int i;
	
	i = 0;
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
		printf ("the nbr of arguments isn't enough or more than the expected!!");
		return (1);
	}
	ft_philo(ac, av);
}
