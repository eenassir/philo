/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:24:45 by eenassir          #+#    #+#             */
/*   Updated: 2024/07/28 23:49:20 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *f(void *arg)
{
	printf ("%s\n", arg);
	return (NULL);
}

int main(int ac, char **av)
{
	pthread_t thread;
	int i;
	int j;

	j = 1;
	while (j < ac)
	{
		i = pthread_create(&thread, NULL, f, av[j]);
		i = pthread_join(thread, NULL);
		j++;
	}
}