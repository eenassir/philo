/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:36:32 by eenassir          #+#    #+#             */
/*   Updated: 2024/10/06 11:17:05 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_meals(t_list *philo)
{
	int				i;
	int				full;

	i = 0;
	full = 0;
	while (i < philo->num_philo)
	{
		pthread_mutex_lock(&philo->init->lock);
		if (philo[i].n_meals_must_eat == 0)
			full++;
		pthread_mutex_unlock(&philo->init->lock);
		i++;
	}
	if (full == philo->num_philo)
	{
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	int		i;
	t_list	*philo;

	philo = (t_list *)arg;
	while (1)
	{
		if (ft_meals(philo) == 1)
			return (NULL);
		i = -1;
		while (++i < philo->init->num_philo)
		{
			pthread_mutex_lock(&philo->init->time);
			if (((get_current_time() - philo->run - \
			philo[i].last_meal)) >= philo->time_to_die)
			{
				philo->init->stop_simul = 1;
				printf ("%lld %d died\n", \
				(get_current_time() - philo->run), philo[i].id);
				pthread_mutex_unlock(&philo->init->time);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->init->time);
		}
	}
	return (NULL);
}
