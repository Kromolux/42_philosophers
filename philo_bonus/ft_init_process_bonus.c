/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:23:04 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/13 10:47:19 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		philo->pid[i] = pid;
		i++;
	}
	return (1);
}

void	ft_destroy_processes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_philos)
	{
		if (kill(philo->pid[i], 0) != -1)
			kill(philo->pid[i], SIGTERM);
		i++;
	}
}
