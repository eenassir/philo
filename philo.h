/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:24:34 by eenassir          #+#    #+#             */
/*   Updated: 2024/07/28 14:56:38 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

typedef struct s_list
{
	int i;
	int c;
	struct s_list *next;
} t_list;

int ft_strlen (char *s);
t_list *ft_lst_new(void);
void ft_free_lst(t_list *lst);

#endif