/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_process_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:59:42 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/29 18:37:31 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_prepare_philo(t_philo *philo, int i)
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
	philo->status = THINKING;
	ft_philo_status(philo, THINKING);
}

int	ft_dead_with_fork(t_philo *philo)
{
	sem_wait(philo->thread_sema);
	if (philo->dead == 1)
	{
		printf("died with fork!\n");
		philo->status = DEAD;
		sem_post(philo->forks_sema);
		sem_post(philo->forks_sema);
		sem_post(philo->thread_sema);
		return (1);
	}
	sem_post(philo->thread_sema);
	return (0);
}
