/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:58:18 by eenassir          #+#    #+#             */
/*   Updated: 2024/10/06 22:21:58 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

long g_c_t(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void ft_usleep(long time)
{
	long long start;

	start = g_c_t();
	while ((g_c_t() - start) < time)
		usleep(100);
}

void ft_printf(char *s, t_list *philo)
{
		sem_wait(philo->data->sem_w);
			printf ("%lld %d %s\n", (g_c_t() - philo->data->run_time), philo->id, s);
		if (philo->data->stop_sim == 0)
			sem_post(philo->data->sem_w);
}

void *ft_monitor(void *arg)
{
	t_list *philo;

	philo = (t_list *)arg;
	while (1)
	{
			sem_wait(philo->data->sem_time);
			if (g_c_t() - philo->last_meal_time > philo->data->time_to_die)
			{
				
				philo->data->stop_sim = 1;
				sem_post(philo->data->sem_death);
				ft_printf("is died", philo);
				return (NULL);
			}
			sem_post(philo->data->sem_time);
	}
	return (NULL);
}


void life(t_list *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	pthread_create(&philo->lock, NULL, ft_monitor, philo);
	pthread_detach(philo->lock);
	while (1)
	{
		sem_wait(philo->data->fork);
		ft_printf("has take a fork", philo);
		
		sem_wait(philo->data->fork);
		ft_printf("has take a fork", philo);
		
		sem_wait(philo->data->sem_time);
		ft_printf("is eating", philo);
		philo->last_meal_time = g_c_t();
		philo->meals_must_eat--;
		sem_post(philo->data->sem_time);
		ft_usleep(philo->data->time_to_eat);
		
		
		sem_post(philo->data->fork);
		sem_post(philo->data->fork);
		
		ft_printf("is sleeping", philo);
		ft_usleep(philo->data->time_to_sleep);
		ft_printf("is thinking", philo);
	}
	exit (0);
}

void ft_init(int *infos)
{
	t_list *philo;
	t_data *part;
	int i;
	
	philo = (t_list *)malloc(sizeof(t_list) * infos[0]);
	part = (t_data *)malloc(sizeof (t_data));
	sem_unlink("/forks");
	sem_unlink("/sem_w");
	sem_unlink("/sem_time");
	sem_unlink("/death");
	part->fork = sem_open("/forks", O_CREAT, 0644, infos[0]);
	if (part->fork == SEM_FAILED)
		return ;
	part->sem_w = sem_open("/sem_w", O_CREAT, 0644, 1);
	if (part->sem_w == SEM_FAILED)
		return ;
	part->sem_time = sem_open("/sem_time", O_CREAT, 0644, 1);
	if (part->sem_time == SEM_FAILED)
		return ;
	part->sem_death = sem_open("/death", O_CREAT, 0644, 1);
	if (part->fork == SEM_FAILED)
		return ;
	part->num = infos[0];
	part->time_to_die = infos[1];
	part->time_to_eat = infos[2];
	part->time_to_sleep = infos[3];
	part->run_time = g_c_t();
	part->stop_sim = 0;
	i = 0;
	while (i < infos[0])
	{
		philo[i].id = i + 1;
		philo[i].last_meal_time = g_c_t();
		philo[i].meals_must_eat = infos[4];
		philo[i].data = part;
		i++;
	}
	i = 0;
	sem_wait(philo->data->sem_death);
	while (i < infos[0])
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
		{
			printf ("error\n");
			return ;
		}
		else if (philo[i].pid == 0)
			life(&philo[i]);
		i++;
	}
	sem_wait(philo->data->sem_death);
	i = 0;
	while (i < infos[0])
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
	i = 0;
	while (i < infos[0])
	{
		waitpid(philo[i].pid, NULL, 0);
		i++;
	}
}

int main(int ac, char **av)
{
	int infos[5];
	
	infos[0] = ft_atoi(av[1]);
	infos[1] = ft_atoi(av[2]);
	infos[2] = ft_atoi(av[3]);
	infos[3] = ft_atoi(av[4]);
	if (ac == 6)
		infos[4] = ft_atoi(av[5]);
	else
		infos[4] = -1;
	ft_init(infos);
}