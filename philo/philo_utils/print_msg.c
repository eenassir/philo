/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:16:28 by eenassir          #+#    #+#             */
/*   Updated: 2024/10/07 22:28:32 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(char *s, t_list *philo)
{
	pthread_mutex_lock(&philo->init->time);
	if (philo->init->stop_simul)
	{
		pthread_mutex_unlock(&philo->init->write_mutex);
		pthread_mutex_unlock(&philo->init->time);
		return ;
	}
	pthread_mutex_unlock(&philo->init->time);
	pthread_mutex_lock(&philo->init->write_mutex);
	printf ("%lld %d %s\n",
		(get_current_time() - philo->run), philo->id, s);
	pthread_mutex_unlock(&philo->init->write_mutex);
}
