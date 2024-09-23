/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:04:57 by eenassir          #+#    #+#             */
/*   Updated: 2024/09/23 14:40:57 by eenassir         ###   ########.fr       */
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
	philo->last_meal = (get_current_time() - philo->run);
	pthread_mutex_unlock(&philo->init->time);
	print_msg("is eating", philo);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_msg("is sleeping", philo);
	ft_usleep(philo->time_to_sleep);
	print_msg("is thinking", philo);
}

void	*life_cycle(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat + 2);
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
		if (pthread_create(&th[i], NULL, life_cycle, &philo[i]) == -1)
			return (printf ("Error\n"), -1);
	}
	i = -1;
	ft_monitor(philo);
	while (++i < init->num_philo)
	{
		if (pthread_join(th[i], NULL) == -1)
			return (printf ("Error\n"), -1);
	}
	free (init->forks);
	return (0);
}

int	main(int ac, char **av)
{
	t_init	init;

	if (ac != 5 && ac != 6)
	{
		printf("The number of arguments isn't \
		the expected nbr to run the simulation!\n");
		return (1);
	}
	if (ft_parcing(ac, av) == -1)
		return (1);
	if (ft_num(ac, av, &init) == -1)
		return (printf("Error\n"), 1);
	if (ft_philo(&init))
		return (printf ("Error\n"), 1);
	return (0);
}
