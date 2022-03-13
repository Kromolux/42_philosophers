/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_to_long_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:30:46 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/12 09:10:46 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_sign(const char *str, int *i_str);

long	ft_string_to_long(const char *nptr)
{
	long	output;
	int		sign;
	int		i;

	output = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	sign = check_sign(nptr, &i);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		output *= 10;
		output += nptr[i] - '0';
		i++;
	}
	return (output * sign);
}

static int	check_sign(const char *str, int *i_str)
{
	int	sign;
	int	i;

	i = *i_str;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	*i_str = i;
	return (sign);
}
