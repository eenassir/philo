/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:24:34 by eenassir          #+#    #+#             */
/*   Updated: 2024/10/04 21:07:23 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include "structs.h"
# include "utils.h"

long long	get_current_time(void);
void		ft_usleep(long time, t_list *philo);
void		print_msg(char *s, t_list *philo);
void		*ft_monitor(void *arg);
int			ft_parcing(int ac, char **av);
int			ft_num(int ac, char **av, t_init *init);
void		*ft_loop(t_init *init, t_list *philo);
void		join(pthread_t *th, t_init *init);

#endif