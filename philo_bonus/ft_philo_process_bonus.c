/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_process_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:08:22 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/16 20:03:58 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_philo_loop(t_philo *philo);
static int	ft_eat(t_philo *philo);
static void	ft_sleep(t_philo *philo);
static void	*ft_check_life_time(void *input);

void	ft_philosopher(t_philo *philo, int i)
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
	ft_philo_status(philo, THINKING);
	philo->thread_sema = ft_sema_init(philo->name, 1);
	sem_wait(philo->start_sema);
	sem_wait(philo->thread_sema);
	sem_post(philo->start_sema);
	pthread_create(&philo->life_check_thread, NULL, &ft_check_life_time, (void * ) philo);
	gettimeofday(&philo->life_time, NULL);
	philo->start_time = philo->life_time;
	sem_post(philo->thread_sema);
	ft_philo_loop(philo);
	sem_post(philo->thread_sema);
	//write(1, "wait for thread to join\n", 24);
	pthread_join(philo->life_check_thread, NULL);
	usleep(100);
	sem_close(philo->dead_sema);
	sem_close(philo->start_sema);
	sem_close(philo->forks_sema);
	sem_close(philo->meals_sema);
	sem_close(philo->thread_sema);
	sem_close(philo->terminal_sema);
	//write(1, "philo process exited\n", 28);
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
			sem_wait(philo->thread_sema);
			ft_philo_status(philo, THINKING);
			sem_post(philo->thread_sema);
		}
	}
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	sem_wait(philo->forks_sema);
	sem_wait(philo->thread_sema);
	if (philo->dead == 1)
	{
		sem_post(philo->forks_sema);
		sem_post(philo->thread_sema);
		return (-1);
	}
	gettimeofday(&philo->actual_time, NULL);
	ft_philo_status(philo, FORK);
	sem_post(philo->thread_sema);
	sem_wait(philo->forks_sema);
	sem_wait(philo->thread_sema);
	if (philo->dead == 1)
	{
		sem_post(philo->forks_sema);
		sem_post(philo->thread_sema);
		return (-1);
	}
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
	philo->meals++;
	if (philo->all_ate == 0 && philo->meals >= philo->num_meals)
	{
		sem_post(philo->meals_sema);
		philo->all_ate = 1;
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
			break;
		gettimeofday(&philo->actual_time, NULL);
		if (ft_get_time_delta(philo->life_time, philo->actual_time)
			>= philo->time_die)
		{
			philo->dead = 1;
			ft_philo_status(philo, DEAD);
			sem_post(philo->thread_sema);
			sem_post(philo->dead_sema);
			//write(1, "philo thread ended\n", 23);
			return (NULL);
		}
		sem_post(philo->thread_sema);
		usleep(1000);
	}
	sem_post(philo->thread_sema);
	//write(1, "philo thread ended\n", 23);
	return (NULL);
}
