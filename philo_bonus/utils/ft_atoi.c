/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eenassir <eenassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:05:33 by eenassir          #+#    #+#             */
/*   Updated: 2024/09/21 15:07:25 by eenassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	ft_atoi(char *s)
{
	int	i;
	int	signe;
	int	result;

	i = 0;
	signe = 1;
	result = 0;
	while (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			signe = -1;
		i++;
	}
	if (i > 1)
		return (printf ("Error\n"), -1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + s[i] - 48;
		if ((result < 0 && signe == 1) || (result * -1 > 0 && signe == -1))
			return (printf ("Error\n"), -1);
		i++;
	}
	return (result * signe);
}
