/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:28:11 by eenassir          #+#    #+#             */
/*   Updated: 2024/10/07 22:33:00 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usleep(long time, t_list *philo)
{
	long	start;
	
	
	start = get_current_time();
	while ((get_current_time() - start) < time)
	{
		pthread_mutex_lock(&philo->init->time);
		if (philo->init->stop_simul == 1)
		{
			pthread_mutex_unlock(&philo->init->time);
			break ;
		}
		pthread_mutex_unlock(&philo->init->time);
		usleep(500);
	}
}
