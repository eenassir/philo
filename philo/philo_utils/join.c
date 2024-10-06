/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:02:29 by eenassir          #+#    #+#             */
/*   Updated: 2024/10/06 22:37:41 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void join(pthread_t *th, t_init *init)
{
	int i;
	
	i = 0;
	while (i < init->num_philo)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&init->write_mutex);
	pthread_mutex_destroy(&init->lock);
	pthread_mutex_destroy(&init->time);
	pthread_mutex_destroy(init->forks);
	free (init->forks);
}