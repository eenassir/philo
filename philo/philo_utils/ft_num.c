/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:21:29 by eenassir          #+#    #+#             */
/*   Updated: 2024/10/04 21:14:12 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_num(int ac, char **av, t_init *init)
{
	init->num_philo = ft_atoi(av[1]);
	if (init->num_philo <= 0 || init->num_philo > 200)
		return (-1);
	init->time_to_die = ft_atoi(av[2]);
	if (init->time_to_die < 60 || init->time_to_die == -1)
		return (-1);
	init->time_to_eat = ft_atoi(av[3]);
	if (init->time_to_eat < 60 || init->time_to_eat == -1)
		return (-1);
	init->time_to_sleep = ft_atoi(av[4]);
	if (init->time_to_sleep < 60 || init->time_to_sleep == -1)
		return (-1);
	if (ac == 6)
	{
		init->n_meals_must_eat = ft_atoi(av[5]);
		if (init->n_meals_must_eat == -1)
			return (-1);
	}
	else
		init->n_meals_must_eat = -1;
	init->stop_simul = 0;
	pthread_mutex_init(&init->write_mutex, NULL);
	pthread_mutex_init(&init->time, NULL);
	pthread_mutex_init(&init->lock, NULL);
	return (0);
}
