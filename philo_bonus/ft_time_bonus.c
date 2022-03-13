/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:13:03 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/12 09:10:52 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_get_time_delta(struct timeval start_time, struct timeval actual_time)
{
	long	delta_sec;
	long	delta_usec;

	delta_sec = actual_time.tv_sec - start_time.tv_sec;
	delta_usec = actual_time.tv_usec - start_time.tv_usec;
	return (delta_sec * 1000000 + delta_usec);
}
