/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:41:46 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/05 11:27:52 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_arguments(t_props *props, char **input)
{
	props->num_philos = (int) ft_string_to_long(input[1]);
	props->time_die = ft_string_to_long(input[2]) * 1000;
	props->time_eat = ft_string_to_long(input[3]) * 1000;
	props->time_sleep = ft_string_to_long(input[4]) * 1000;
	if (input[5])
		props->num_meals = ft_string_to_long(input[5]);
	else
		props->num_meals = 0;
	if (props->num_philos <= 0 || props->num_philos > 200)
		return (ft_error_num_philos());
	if (props->time_die <= (props->time_eat + props->time_sleep))
		return (ft_error_time_die());
	return (1);
}
