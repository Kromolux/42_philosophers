/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:15:00 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/15 11:16:06 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_get_str_len(long n, int sign);
static int		check_sign(const char *str, int *i_str);

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
