/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_semaphore_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:45:08 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/29 18:35:50 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*ft_sema_init(char *name, int value)
{
	sem_t	*sema;

	//sema = sem_open(name, O_CREAT | O_EXCL, 0755, value);
	//if (sema != SEM_FAILED)
	//	return (sema);
	sem_unlink(name);
	sema = sem_open(name, O_CREAT, 0655, value);
	return (sema);
}

void	ft_init_main_sema(t_philo *philo)
{
	philo->forks_sema = ft_sema_init("forks", philo->num_philos);
	philo->terminal_sema = ft_sema_init("terminal", 1);
	philo->meals_sema = ft_sema_init("meals", 0);
	philo->dead_sema = ft_sema_init("dead", 0);
	philo->start_sema = ft_sema_init("start", 0);
	philo->thread_sema = ft_sema_init("thread", 1);
	printf("sema %i, %i, %i, %i, %i, %i\n", (int) philo->forks_sema, (int)philo->terminal_sema, (int)philo->meals_sema, (int)philo->dead_sema, (int)philo->start_sema, (int)philo->thread_sema);
	//philo->status = THINKING;
}

void	ft_close_all_sema(t_philo *philo)
{
	sem_close(philo->terminal_sema);
	sem_close(philo->dead_sema);
	sem_close(philo->start_sema);
	sem_close(philo->meals_sema);
	sem_close(philo->forks_sema);
	sem_close(philo->thread_sema);
}
