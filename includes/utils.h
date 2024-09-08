/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:12:23 by eenassir          #+#    #+#             */
/*   Updated: 2024/09/08 11:41:44 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include "philo.h"

int ft_strlen (char *s);
t_list *ft_lst_new(void);
void ft_free_lst(t_list **lst);
int ft_atoi(char *s);
int ft_strcmp(char *s1, char *s2);

#endif