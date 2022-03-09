/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:26:03 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/05 11:25:59 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_arguments(void)
{
	printf("Error! Program needs at least 4 and max 5 arguments!\n./philo <number_of_philosophers>"
		" <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
	return (-1);
}

int	ft_error_malloc(char *function, char *variable, size_t size)
{
	printf("Error! Not enough memory for allocating space for [%s] [%li]"
		"bytes by function: %s\n", variable, size, function);
	return (0);
}

int	ft_error_num_philos(void)
{
	printf("Error! Number of Philosophers must between 1 and 200, 1 <= num_philos <= 200!\n");
	return (0);
}

int	ft_error_time_die(void)
{
	printf("Error! Time to die must be bigger than time_to_eat + time_to_sleep!\n");
	return (0);
}
