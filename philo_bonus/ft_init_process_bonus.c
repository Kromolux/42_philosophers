/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:23:04 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/29 18:20:31 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_collect_semas(t_philo *philo);

int	ft_init_processes(t_philo *philo)
{
	int		i;
	pid_t	pid;

	philo->pid = (pid_t *) malloc(sizeof(pid_t) * philo->num_philos);
	if (!philo->pid)
		return (0);
	i = 0;
	while (i < philo->num_philos)
	{
		pid = fork();
		if (pid == 0)
			ft_philosopher(philo, i);
		if (pid < 0)
			return (ft_error_create_philos());
		philo->pid[i] = pid;
		i++;
	}
	return (1);
}

void	ft_destroy_processes(t_philo *philo)
{
	int	i;

	ft_collect_semas(philo);
	usleep(philo->time_die);
	i = 0;
	while (i < philo->num_philos)
	{
		sem_post(philo->forks_sema);
		sem_post(philo->start_sema);
		i++;
	}
	i = 0;
	while (i < philo->num_philos)
	{
		waitpid(philo->pid[i], NULL, 0);
		i++;
	}
	free(philo->pid);
}

static void	ft_collect_semas(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philos)
	{
		sem_wait(philo->start_sema);
		i++;
	}
	i = 0;
}
