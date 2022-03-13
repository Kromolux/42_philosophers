/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_meals_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:36:12 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/13 13:29:37 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_check_meals(void *input)
{
	t_philo	*philo;
	int	i;

	i = 0;
	philo = (t_philo *) input;
	while (i < philo->num_philos)
	{
		sem_wait(philo->meals_sema);
		i++;
	}
	sem_post(philo->dead_sema);
	philo->all_ate = 1;
	return (NULL);
}

void	*ft_check_dead(void *input)
{
	t_philo	*philo;

	philo = (t_philo *) input;
	sem_wait(philo->dead_sema);
	ft_destroy_processes(&philo);
	return (NULL);
}

void	*ft_send_life_signal(void *input)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *) input;
	while (1)
	{
		i = 0;
		while (i < philo->num_philos)
		{
			kill(philo->pid[i], SIGSTOP);
			kill(philo->pid[i], SIGCONT);
			i++;
		}
		usleep(5000);
	}
	return (NULL);
}
