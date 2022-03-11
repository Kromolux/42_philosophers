/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_thread1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 13:06:35 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/11 17:49:44 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_life_time(t_philos *philo)
{
	if (ft_get_time_delta(philo->life_time, philo->actual_time)
		>= philo->props.time_die)
	{
		philo->stop = 1;
		philo->status = DEAD;
		ft_philo_status(philo, 0);
	}
}

int	ft_check_meals(t_philos *philos, t_props *props)
{
	int	i;

	if (props->num_meals == 0)
		return (0);
	i = 0;
	pthread_mutex_lock(&philos->times->meal_lock);
	while (i < props->num_philos)
	{
		if (philos[i].meals < props->num_meals)
		{
			pthread_mutex_unlock(&philos->times->meal_lock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&philos->times->meal_lock);
	philos->times->all_ate = props->num_meals;
	return (1);
}
