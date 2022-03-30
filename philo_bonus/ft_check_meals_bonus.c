/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_meals_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:36:12 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/30 09:43:23 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_check_meals(void *input)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *) input;
	while (i < philo->num_philos && philo->dead == 0)
	{
		sem_wait(philo->meals_sema);
		i++;
	}
	if (philo->dead == 0)
		philo->all_ate = 1;
	sem_post(philo->dead_sema);
	return (NULL);
}
