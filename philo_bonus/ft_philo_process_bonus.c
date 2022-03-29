/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_process_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:08:22 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/29 18:34:26 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_philo_loop(t_philo *philo);
static int	ft_eat(t_philo *philo);
static void	ft_sleep(t_philo *philo);

void	ft_philosopher(t_philo *philo, int i)
{
	ft_prepare_philo(philo, i);
	sem_wait(philo->start_sema);
	sem_post(philo->start_sema);
	gettimeofday(&philo->life_time, NULL);
	philo->start_time = philo->life_time;
	pthread_create(&philo->life_check_thread, NULL,
		&ft_check_life_time, (void *) philo);
	ft_philo_loop(philo);
	sem_post(philo->thread_sema);
	pthread_join(philo->life_check_thread, NULL);
	ft_close_all_sema(philo);
	exit(1);
}

static int	ft_philo_loop(t_philo *philo)
{
	usleep(philo->myturn * (philo->time_sleep - 20000));
	while (1)
	{
		sem_wait(philo->thread_sema);
		sem_wait(philo->start_sema);
		sem_post(philo->start_sema);
		gettimeofday(&philo->actual_time, NULL);
		philo->d_action_time = ft_get_time_delta(
				philo->action_time, philo->actual_time);
		//printf("checking for alive and all ate\n");
		if (philo->dead == 1 || philo->all_ate == 1)
		{
			ft_philo_status(philo, DEBUG);
			printf("leave loop with dead == 1 from endless loop\n");
			break ;
		}
		sem_post(philo->thread_sema);
		if (philo->status == THINKING)
		{
			if (ft_eat(philo) == -1)
				break ;
		}
		else if (philo->status == EATING && philo->d_action_time
			>= philo->time_eat)
			ft_sleep(philo);
		else if (philo->status == SLEEPING && philo->d_action_time
			>= philo->time_sleep)
		{
			philo->status = THINKING;
			ft_philo_status(philo, THINKING);
		}
	}
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	sem_wait(philo->forks_sema);
	if (ft_dead_with_fork(philo))
		return (-1);
	sem_wait(philo->thread_sema);
	gettimeofday(&philo->actual_time, NULL);
	sem_post(philo->thread_sema);
	ft_philo_status(philo, FORK);
	printf("waiting for second fork\n");
	sem_wait(philo->forks_sema);
	if (ft_dead_with_fork(philo))
		return (-1);
	sem_wait(philo->thread_sema);
	gettimeofday(&philo->actual_time, NULL);
	ft_philo_status(philo, FORK);
	gettimeofday(&philo->action_time, NULL);
	philo->life_time = philo->action_time;
	philo->status = EATING;
	sem_post(philo->thread_sema);
	ft_philo_status(philo, EATING);
	usleep(philo->time_eat - 10000);
	return (0);
}

static void	ft_sleep(t_philo *philo)
{
	sem_post(philo->forks_sema);
	sem_post(philo->forks_sema);
	sem_wait(philo->thread_sema);
	if (philo->dead == 1)
	{
		philo->status = DEAD;
		sem_post(philo->thread_sema);
		return ;
	}
	if (philo->num_meals > 0)
	{
		philo->meals++;
		if (philo->all_ate == 0 && philo->meals >= philo->num_meals)
		{
			sem_post(philo->meals_sema);
			philo->all_ate = 1;
		}
	}
	gettimeofday(&philo->action_time, NULL);
	philo->status = SLEEPING;
	ft_philo_status(philo, SLEEPING);
	sem_post(philo->thread_sema);
	usleep(philo->time_sleep - 10000);
}
