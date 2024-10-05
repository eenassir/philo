/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:02:29 by eenassir          #+#    #+#             */
/*   Updated: 2024/10/04 21:06:01 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void join(pthread_t *th, t_init *init)
{
	int i;

	i = 0;
	while (pthread_join(th[i++], NULL) == 0)
		;
	free (init->forks);
}