/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arguments_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:41:46 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/12 15:02:00 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_error_time_eat(long time);
static int	ft_error_time_sleep(long time);
static int	ft_error_num_meals(int meals);

int	ft_get_arguments(t_philo *philo, char **input)
{
	philo->num_philos = (int) ft_string_to_long(input[1]);
	philo->time_die = ft_string_to_long(input[2]) * 1000;
	philo->time_eat = ft_string_to_long(input[3]) * 1000;
	philo->time_sleep = (int) ft_string_to_long(input[4]) * 1000;
	if (input[5])
		philo->num_meals = ft_string_to_long(input[5]);
	else
		philo->num_meals = 0;
	if (philo->num_meals > 1000)
		return (ft_error_num_meals(philo->num_meals));
	if (philo->num_philos <= 0 || philo->num_philos > 200)
		return (ft_error_num_philos());
	if (philo->time_die <= (philo->time_eat + philo->time_sleep)
		|| philo->time_die > 10000000)
		return (ft_error_time_die());
	if (philo->time_eat < 60000 || philo->time_eat > 1000000)
		return (ft_error_time_eat(philo->time_eat));
	if (philo->time_sleep < 60000 || philo->time_sleep > 1000000)
		return (ft_error_time_sleep(philo->time_sleep));
	return (1);
}

static int	ft_error_time_eat(long time)
{
	printf(COLOR_RED
		"Error! Time to eat %lu is to small, must >= 60 ms and <= 1000 ms\n"
		COLOR_DEFAULT, time / 1000);
	return (0);
}

static int	ft_error_time_sleep(long time)
{
	printf(COLOR_RED
		"Error! Time to sleep %lu is invalid, must >= 60 ms and <= 1000 ms\n"
		COLOR_DEFAULT, time / 1000);
	return (0);
}

static int	ft_error_num_meals(int meals)
{
	printf(COLOR_RED
		"Error! Number of meals %i is invalid, must >= 0 and <= 1000\n"
		COLOR_DEFAULT, meals);
	return (0);
}
