/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:34:00 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/11 10:50:29 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_write_string(char *s)
{
	size_t	i;

	i = ft_strlen(s);
	write(1, s, i);
	free((void *) s);
	return (0);
}
