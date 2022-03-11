/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:08:22 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/11 18:07:23 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_think(t_philos *philo);
static void	ft_eat(t_philos *philo);
static void	ft_take_forks(t_philos *philo);
static void	ft_sleep(t_philos *philo);

void	*ft_philo_thread(void *input)
{
	t_philos	*philo;

	philo = (t_philos *) input;
	usleep(philo->myturn * (philo->props.time_sleep - 20000));
	while (1)
	{
		gettimeofday(&philo->actual_time, NULL);
		philo->d_action_time = ft_get_time_delta(philo->action_time,
				philo->actual_time);
		pthread_mutex_lock(&philo->thread_lock);
		if (philo->stop == 1)
			break ;
		ft_check_life_time(philo);
		pthread_mutex_unlock(&philo->thread_lock);
		if (philo->status == THINKING)
			ft_eat(philo);
		else if (philo->status == EATING && philo->d_action_time
			>= philo->props.time_eat)
			ft_sleep(philo);
		else if (philo->status == SLEEPING && philo->d_action_time
			>= philo->props.time_sleep)
			ft_think(philo);
	}
	pthread_mutex_unlock(&philo->thread_lock);
	return (NULL);
}

static void	ft_think(t_philos *philo)
{
	philo->status = THINKING;
	ft_philo_status(philo, 0);
}

static void	ft_eat(t_philos *philo)
{
	ft_take_forks(philo);
	if (philo->has_left_fork && philo->has_right_fork)
	{
		gettimeofday(&philo->action_time, NULL);
		pthread_mutex_lock(&philo->thread_lock);
		philo->life_time = philo->action_time;
		philo->status = EATING;
		pthread_mutex_unlock(&philo->thread_lock);
		ft_philo_status(philo, 0);
		usleep(philo->props.time_eat - 20000);
	}
}

static void	ft_take_forks(t_philos *philo)
{
	if (philo->has_right_fork == 0)
	{
		pthread_mutex_lock(&philo->right_fork_lock);
		if (philo->right_fork == 1)
		{
			philo->has_right_fork = 1;
			philo->right_fork = 0;
			ft_philo_status(philo, 1);
		}
		pthread_mutex_unlock(&philo->right_fork_lock);
	}
	if (philo->props.num_philos > 1 && philo->has_left_fork == 0)
	{
		pthread_mutex_lock(philo->left_fork_lock);
		if (*philo->left_fork == 1)
		{
			philo->has_left_fork = 1;
			*philo->left_fork = 0;
			ft_philo_status(philo, 1);
		}
		pthread_mutex_unlock(philo->left_fork_lock);
	}
}

static void	ft_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->right_fork_lock);
	philo->has_right_fork = 0;
	philo->right_fork = 1;
	pthread_mutex_unlock(&philo->right_fork_lock);
	pthread_mutex_lock(philo->left_fork_lock);
	philo->has_left_fork = 0;
	*philo->left_fork = 1;
	pthread_mutex_unlock(philo->left_fork_lock);
	pthread_mutex_lock(&philo->times->meal_lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->times->meal_lock);
	gettimeofday(&philo->action_time, NULL);
	philo->status = SLEEPING;
	ft_philo_status(philo, 0);
	usleep(philo->props.time_sleep - 20000);
}
