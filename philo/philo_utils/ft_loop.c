/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:23:02 by eenassir          #+#    #+#             */
/*   Updated: 2024/09/22 12:23:38 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_loop(t_init *init, t_list *philo)
{
	int	i;

	i = 0;
	init->forks = malloc(sizeof (pthread_mutex_t) * init->num_philo);
	if (!init->forks)
		return (NULL);
	while (i < init->num_philo)
		pthread_mutex_init(&init->forks[i++], NULL);
	i = 0;
	while (i < init->num_philo)
	{
		philo[i].init = init;
		philo[i].id = i + 1;
		philo[i].num_philo = init->num_philo;
		philo[i].time_to_die = init->time_to_die;
		philo[i].time_to_sleep = init->time_to_sleep;
		philo[i].time_to_eat = init->time_to_eat;
		philo[i].n_meals_must_eat = init->n_meals_must_eat;
		philo[i].last_meal = init->start;
		philo[i].left_fork = &init->forks[i];
		philo[i].right_fork = &init->forks[((i + 1) % init->num_philo)];
		i++;
	}
	return (NULL);
}
