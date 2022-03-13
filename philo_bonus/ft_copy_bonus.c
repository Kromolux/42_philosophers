/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:30:47 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/12 09:10:13 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_copy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		size--;
		while (i < size && src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (i);
}
