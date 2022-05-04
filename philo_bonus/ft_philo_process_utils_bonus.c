/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_process_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:59:42 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/30 11:18:29 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_prepare_philo(t_philo *philo, int i)
{
	char	*tmp;

	free(philo->pid);
	tmp = ft_long_to_string((long) i + 1);
	ft_copy(philo->name, tmp, 0);
	free(tmp);
	if ((philo->num_philos % 2) == 0)
		philo->myturn = i % 2;
	else
		philo->myturn = i % 3;
	philo->status = THINKING;
}

int	ft_is_dead_with_fork(t_philo *philo)
{
	if (!ft_is_alive(philo))
	{
		sem_post(philo->forks_sema);
		sem_post(philo->forks_sema);
		return (1);
	}
	return (0);
}

int	ft_is_alive(t_philo *philo)
{
	gettimeofday(&philo->actual_time, NULL);
	if (ft_get_time_delta(philo->life_time, philo->actual_time)
		>= philo->time_die)
	{
		philo->status = DEAD;
		return (0);
	}
	else
		return (1);
}

int	ft_get_time_d(t_philo *philo)
{
	gettimeofday(&philo->actual_time, NULL);
	philo->d_action_time = ft_get_time_delta(
			philo->action_time, philo->actual_time);
	return (0);
}
