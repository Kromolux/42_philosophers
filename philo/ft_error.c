/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:26:03 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/11 15:38:54 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_arguments(void)
{
	printf(COLOR_RED
		"Error! Program needs at least 4 and max 5 arguments!\n./philo "
		"<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>"
		" [number_of_times_each_philosopher_must_eat]\n"
		"All times are in ms and numbers are unsigned int\n"
		COLOR_DEFAULT);
	return (0);
}

int	ft_error_malloc(char *function, char *variable, size_t size)
{
	printf(COLOR_RED
		"Error! Not enough memory for allocating space for [%s] [%li]"
		"bytes by function: %s\n"COLOR_DEFAULT, variable, size, function);
	return (0);
}

int	ft_error_num_philos(void)
{
	printf(COLOR_RED
		"Error! Number of Philosophers must between 1 and 200, 1 <= "
		"num_philos <= 200!\n"COLOR_DEFAULT);
	return (0);
}

int	ft_error_time_die(void)
{
	printf(COLOR_RED
		"Error! Time to die must be bigger than time_to_eat +"
		" time_to_sleep!\n" COLOR_DEFAULT);
	return (0);
}

int	ft_error_create_philos(void)
{
	printf(COLOR_RED
		"Error!, Was not able to create threads\n" COLOR_DEFAULT);
	return (0);
}
