/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:04:57 by eenassir          #+#    #+#             */
/*   Updated: 2024/10/07 22:32:01 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	ft_life(t_list *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(&philo->init->lock);
	philo->n_meals_must_eat--;
	pthread_mutex_unlock(&philo->init->lock);
	pthread_mutex_lock(&philo->init->time);
	philo->last_meal = get_current_time() - philo->run;
	pthread_mutex_unlock(&philo->init->time);
	print_msg("is eating", philo);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_msg("is sleeping", philo);
	ft_usleep(philo->time_to_sleep, philo);
	print_msg("is thinking", philo);
}

void	*life_cycle(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(&philo->init->time);
		if (philo->n_meals_must_eat == 0 || philo->init->stop_simul == 1)
		{
			pthread_mutex_unlock(&philo->init->time);
			break ;
		}
		pthread_mutex_unlock(&philo->init->time);
		pthread_mutex_lock(philo->left_fork);
		print_msg("has taken a fork", philo);
		if (philo->init->num_philo == 1)
		{
			philo->init->stop_simul = 1;
			pthread_mutex_unlock(philo->left_fork);
		}
		ft_life(philo);
	}
	return (NULL);
}

int	ft_philo(t_init *init)
{
	int			i;
	int			ret;
	pthread_t	th[200];
	t_list		philo[200];

	ft_loop(init, philo);
	i = -1;
	init->start = get_current_time();
	while (++i < init->num_philo)
		philo[i].run = init->start;
	i = -1;
	while (++i < init->num_philo)
	{
		ret = pthread_create(&th[i], NULL, life_cycle, &philo[i]);
		if (ret != 0)
		{
			join(th, init);
			return (1);
		}
	}
	ft_monitor(philo);
	join(th, init);
	return (0);
}

int	main(int ac, char **av)
{
	t_init	init;

	if (ac != 5 && ac != 6)
		return (printf ("Error\n"), 1);
	if (ft_parcing(ac, av) == -1)
		return (printf ("Error\n"), 1);
	if (ft_num(ac, av, &init) == -1)
		return (printf("Error\n"), 1);
	if (ft_philo(&init) == 1)
		return (printf ("Error\n"), 1);
	return (0);
}
