/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_to_string_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:36:28 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/12 09:10:27 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_get_str_len(long n, int sign);

char	*ft_long_to_string(long n)
{
	char	*output;
	long	tmp;
	size_t	i;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	tmp = (long) n * sign;
	i = ft_get_str_len(tmp, sign);
	output = malloc(i + 1);
	if (!output)
		return (NULL);
	output[i--] = '\0';
	while (tmp > 9)
	{
		output[i] = (char)(tmp % 10) + '0';
		tmp = tmp / 10;
		i--;
	}
	output[i] = (char)(tmp % 10) + '0';
	if (sign == -1)
		output[0] = '-';
	return (output);
}

static size_t	ft_get_str_len(long n, int sign)
{
	size_t	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	if (sign == -1)
		i++;
	return (i);
}
