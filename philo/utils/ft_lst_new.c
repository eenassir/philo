/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:18:59 by eenassir          #+#    #+#             */
/*   Updated: 2024/09/08 11:44:40 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

t_list *ft_lst_new(void)
{
	t_list *new;

	new = (t_list *)malloc(sizeof (t_list));
	if (!new)
		return (NULL);
	// new->next = NULL;
	return (new);
}