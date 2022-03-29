/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_thread_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 08:20:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/29 18:17:05 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_check_life_time(void *input)
{
	t_philo	*philo;

	philo = (t_philo *) input;
	while (1)
	{
		sem_wait(philo->thread_sema);
		gettimeofday(&philo->actual_time, NULL);
		if (ft_get_time_delta(philo->life_time, philo->actual_time)
			>= philo->time_die)
		{
			ft_philo_status(philo, DEAD);
			ft_philo_status(philo, DEBUG);
			sem_post(philo->dead_sema);
			philo->dead = 1;
			break ;
		}
		if (philo->all_ate == 1)
			break ;
		sem_post(philo->thread_sema);
	}
	sem_post(philo->thread_sema);
	return (NULL);
}
