/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:24:45 by eenassir          #+#    #+#             */
/*   Updated: 2024/08/13 18:31:28 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_current_time()
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 100LL) + (time.tv_usec / 1000));
}
void *philosopher_lifecycle(void *arg) {
    t_list *philo = (t_list *)arg;
    
    while (1) {
        // Think
        printf("philosopher %d is thinking\n", philo->id);
		
        
        // Pick up forks (mutex lock)
        pthread_mutex_lock(philo->left_fork);
        printf("philosopher %d has taken a fork\n", philo->id);
        pthread_mutex_lock(philo->right_fork);
        printf("philosopher %d has taken a fork\n", philo->id);
        
        // Eat
        philo->last_meal_time = get_current_time();
        printf("philosopher %d is eating\n", philo->id);
        usleep(philo->time_to_eat * 1000);  // Convert ms to us
        philo->times_eaten++;
        
        // Put down forks (mutex unlock)
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        
        // Sleep
        printf("philosopher %d is sleeping\n", philo->id);
        usleep(philo->time_to_sleep * 1000);  // Convert ms to us
        
        // Check if the philosopher has eaten enough
        if (philo->times_must_eat != -1 && philo->times_eaten >= philo->times_must_eat) {
            break;
        }
    }
    
    return NULL;
}


int main(int ac, char **av)
{
	pthread_t th[ft_atoi(av[1])];
	pthread_mutex_t forks[ft_atoi(av[1])];
	t_list philo[ft_atoi(av[1])];
	int num_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int time_must_eat;
	int i;

	i = 0;
	num_philo = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		time_must_eat = ft_atoi(av[5]);
	else
		time_must_eat = -1;
	while (i < num_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		philo[i].id = i + 1;
		philo[i].time_to_die = time_to_die;
		philo[i].time_to_eat = time_to_eat;
		philo[i].time_to_sleep = time_to_sleep;
		philo[i].times_must_eat = time_must_eat;
		philo[i].times_eaten = 0;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % num_philo];
		philo[i].last_meal_time = get_current_time();
		pthread_create(&th[i], NULL, philosopher_lifecycle, &philo[i]);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_destroy(&forks[i]);
	}
}