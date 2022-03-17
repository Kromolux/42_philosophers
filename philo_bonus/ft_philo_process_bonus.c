/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_process_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:08:22 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/17 18:25:15 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_philo_loop(t_philo *philo);
static int	ft_eat(t_philo *philo);
static void	ft_sleep(t_philo *philo);
static void	*ft_check_life_time(void *input);

void	ft_philosopher(t_philo *philo, int i)
{
	ft_prepare_philo(philo, i);
	sem_wait(philo->start_sema);
	sem_wait(philo->thread_sema);
	sem_post(philo->start_sema);
	pthread_create(&philo->life_check_thread, NULL,
		&ft_check_life_time, (void *) philo);
	gettimeofday(&philo->life_time, NULL);
	philo->start_time = philo->life_time;
	sem_post(philo->thread_sema);
	ft_philo_loop(philo);
	sem_post(philo->thread_sema);
	pthread_join(philo->life_check_thread, NULL);
	usleep(100);
	ft_close_all_sema(philo);
	exit(1);
}

static int	ft_philo_loop(t_philo *philo)
{
	usleep(philo->myturn * (philo->time_sleep - 20000));
	while (1)
	{
		gettimeofday(&philo->actual_time, NULL);
		philo->d_action_time = ft_get_time_delta(
				philo->action_time, philo->actual_time);
		sem_wait(philo->start_sema);
		sem_post(philo->start_sema);
		sem_wait(philo->thread_sema);
		if (philo->dead == 1 || philo->all_ate == 1)
			return (-1);
		sem_post(philo->thread_sema);
		if (philo->status == THINKING)
			ft_eat(philo);
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
	gettimeofday(&philo->actual_time, NULL);
	ft_philo_status(philo, FORK);
	sem_post(philo->thread_sema);
	sem_wait(philo->forks_sema);
	if (ft_dead_with_fork(philo))
		return (-1);
	gettimeofday(&philo->actual_time, NULL);
	ft_philo_status(philo, FORK);
	gettimeofday(&philo->action_time, NULL);
	philo->life_time = philo->action_time;
	philo->status = EATING;
	ft_philo_status(philo, EATING);
	sem_post(philo->thread_sema);
	usleep(philo->time_eat - 30000);
	return (0);
}

static void	ft_sleep(t_philo *philo)
{
	sem_post(philo->forks_sema);
	sem_post(philo->forks_sema);
	sem_wait(philo->thread_sema);
	if (philo->dead == 1)
	{
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
	usleep(philo->time_sleep - 30000);
}

static void	*ft_check_life_time(void *input)
{
	t_philo	*philo;

	philo = (t_philo *) input;
	while (1)
	{
		sem_wait(philo->thread_sema);
		if (philo->all_ate == 1)
			break ;
		gettimeofday(&philo->actual_time, NULL);
		if (ft_get_time_delta(philo->life_time, philo->actual_time)
			>= philo->time_die)
		{
			philo->dead = 1;
			ft_philo_status(philo, DEAD);
			sem_post(philo->thread_sema);
			sem_post(philo->dead_sema);
			return (NULL);
		}
		sem_post(philo->thread_sema);
		usleep(1000);
	}
	sem_post(philo->thread_sema);
	return (NULL);
}
