/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:08:22 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/10 17:07:27 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_thread(void *input)
{
	t_philos	*philo;

	philo = (t_philos *) input;
	while (philo->status != DEAD && philo->meals < philo->props->num_meals)
	{
		if (ft_get_time_delta(&philo->life_time, &philo->times->actual) >= philo->props->time_die)
		{
			philo->status = DEAD;
			ft_philo_status(philo, 0);
		}
		else if (philo->status == THINKING && philo->myturn == philo->times->loop->turn)
		{
			pthread_mutex_lock(&philo->right_fork_lock);
			philo->right_fork = 0;
			ft_philo_status(philo, 1);
			pthread_mutex_lock(philo->left_fork_lock);
			*philo->left_fork = 0;
			ft_philo_status(philo, 1);
			gettimeofday(&philo->action_time, NULL);
			philo->life_time.tv_sec = philo->action_time.tv_sec;
			philo->life_time.tv_usec = philo->action_time.tv_usec;
			philo->status = EATING;
			ft_philo_status(philo, 0);
			usleep(philo->props->time_eat - 20000);
		}
		else if (philo->status == EATING && ft_get_time_delta(&philo->action_time, &philo->times->actual) >= philo->props->time_eat)
		{
			philo->right_fork = 1;
			pthread_mutex_unlock(&philo->right_fork_lock);
			*philo->left_fork = 1;
			pthread_mutex_unlock(philo->left_fork_lock);
			philo->meals++;
			gettimeofday(&philo->action_time, NULL);
			philo->status = SLEEPING;
			ft_philo_status(philo, 0);
			usleep(philo->props->time_sleep - 20000);
		}
		else if (philo->status == SLEEPING && ft_get_time_delta(&philo->action_time, &philo->times->actual) >= philo->props->time_sleep)
		{
			philo->status = THINKING;
			ft_philo_status(philo, 0);
		}
		usleep(100);
	}
	if (philo->status == DEAD)
		philo->props->num_meals = 0;
	return (NULL);
}
