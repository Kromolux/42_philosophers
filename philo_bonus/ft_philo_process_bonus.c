/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_process_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:08:22 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/13 13:54:08 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_philo_loop(t_philo *philo);
static void	ft_eat(t_philo *philo);
static void	ft_sleep(t_philo *philo);
static void	ft_check_life_time(void *input);

void	ft_philosopher(t_philo *philo, int i)
{
	free(philo->pid);
	philo->name = ft_long_to_string((long) i + 1);
	if ((philo->num_philos % 2) == 0)
		philo->myturn = i % 2;
	else
		philo->myturn = i % 3;
	philo->thread_sema = sem_open("thread", O_CREAT, 0777, 1);
	sem_wait(philo->dead_sema);
	pthread_create(&philo->life_signal_thread, NULL, &ft_check_life_time, (void * ) philo);
	gettimeofday(&philo->life_time, NULL);
	philo->start_time = philo->life_time;
	ft_philo_loop(philo);
	free(philo->name);
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
		if (philo->status == THINKING)
			ft_eat(philo);
		else if (philo->status == EATING && philo->d_action_time
			>= philo->time_eat)
			ft_sleep(philo);
		else if (philo->status == SLEEPING && philo->d_action_time
			>= philo->time_sleep)
		{
			philo->status = THINKING;
			ft_philo_status(philo, 0);
		}
	}
	return (0);
}

static void	ft_eat(t_philo *philo)
{
	sem_wait(philo->forks_sema);
	gettimeofday(&philo->actual_time, NULL);
	ft_philo_status(philo, 1);
	sem_wait(philo->forks_sema);
	gettimeofday(&philo->actual_time, NULL);
	ft_philo_status(philo, 1);
	gettimeofday(&philo->action_time, NULL);
	philo->life_time = philo->action_time;
	philo->status = EATING;
	ft_philo_status(philo, 0);
	usleep(philo->time_eat - 30000);
}

static void	ft_sleep(t_philo *philo)
{
	sem_post(philo->forks_sema);
	sem_post(philo->forks_sema);
	philo->meals++;
	if (philo->all_ate == 0 && philo->meals >= philo->num_meals)
	{
		sem_post(philo->meals_sema);
		philo->all_ate = 1;
	}
	gettimeofday(&philo->action_time, NULL);
	philo->status = SLEEPING;
	ft_philo_status(philo, 0);
	usleep(philo->time_sleep - 30000);
}

static void	ft_check_life_time(void *input)
{
	t_philo	*philo;

	philo = (t_philo *) input;
	while (1)
	{
		gettimeofday(&philo->actual_time, NULL);
		if (ft_get_time_delta(philo->life_time, philo->actual_time)
			>= philo->time_die)
		{
			philo->status = DEAD;
			ft_philo_status(philo, 0);
			sem_post(philo->dead_sema);
			return (NULL);
		}
	}
	return (NULL);
}
