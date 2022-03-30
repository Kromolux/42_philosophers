/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_process_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:08:22 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/30 11:19:31 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_philo_loop(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);

void	ft_philosopher(t_philo *philo, int i)
{
	ft_prepare_philo(philo, i);
	sem_wait(philo->start_sema);
	sem_post(philo->start_sema);
	gettimeofday(&philo->life_time, NULL);
	philo->start_time = philo->life_time;
	ft_philo_status(philo, THINKING);
	ft_philo_loop(philo);
	exit(1);
}

void	ft_philo_loop(t_philo *philo_in)
{
	t_philo	philo[1];

	*philo = *philo_in;
	pthread_create(&philo->life_check_thread, NULL,
		&ft_check_life_time, (void *) philo);
	usleep(philo->myturn * (philo->time_sleep - 20000));
	sem_wait(philo->thread_sema);
	while (philo->dead == 0)
	{
		sem_post(philo->thread_sema);
		sem_wait(philo->start_sema);
		sem_post(philo->start_sema);
		if (ft_eat(philo) == -1)
			break ;
		if (ft_sleep(philo) == -1)
			break ;
		ft_think(philo);
		sem_wait(philo->thread_sema);
	}
	sem_wait(philo->thread_sema);
	philo->all_ate = 1;
	sem_post(philo->thread_sema);
	pthread_join(philo->life_check_thread, NULL);
}

int	ft_eat(t_philo *philo)
{
	if (philo->status == THINKING)
	{
		sem_wait(philo->forks_sema);
		if (ft_is_dead_with_fork(philo))
			return (-1);
		ft_philo_status(philo, FORK);
		sem_wait(philo->forks_sema);
		if (ft_is_dead_with_fork(philo))
			return (-1);
		ft_philo_status(philo, FORK);
		gettimeofday(&philo->action_time, NULL);
		philo->life_time = philo->action_time;
		philo->status = EATING;
		ft_philo_status(philo, EATING);
		usleep(philo->time_eat - 10000);
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_get_time_d(philo);
	if (philo->status == EATING && philo->d_action_time
		>= philo->time_eat)
	{
		sem_post(philo->forks_sema);
		sem_post(philo->forks_sema);
		if (!ft_is_alive(philo))
			return (-1);
		gettimeofday(&philo->action_time, NULL);
		philo->status = SLEEPING;
		ft_philo_status(philo, SLEEPING);
		if (philo->num_meals > 0)
		{
			philo->meals++;
			if (philo->all_ate == 0 && philo->meals >= philo->num_meals)
			{
				sem_post(philo->meals_sema);
				return (-1);
			}
		}
		usleep(philo->time_sleep - 10000);
	}
	return (0);
}

int	ft_think(t_philo *philo)
{
	ft_get_time_d(philo);
	if (philo->status == SLEEPING && philo->d_action_time
		>= philo->time_sleep)
	{
		philo->status = THINKING;
		ft_philo_status(philo, THINKING);
	}
	return (0);
}
