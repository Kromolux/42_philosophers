/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:45:19 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/10 15:40:35 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_status(t_philos *philo, int fork)
{
	char	*output;
	char	*time;
	size_t	len;

	time = ft_long_to_string((long) philo->times->delta / 1000);
	len = ft_strlen(time);
	output = (char *) malloc(len + ft_strlen(philo->name) + 23);
	if (!output)
		return (ft_error_malloc("ft_philo_status", "output", (len + ft_strlen(philo->name) + 23)));
	ft_copy(output, time, 0);
	free(time);
	output[len] = ' ';
	ft_copy(&output[len + 1], philo->name, 0);
	len = ft_strlen(output);
	if (fork == 1)
		ft_copy(&output[len], " has taken a fork\n", 0);
	else if (philo->status == EATING)
		ft_copy(&output[len], " is eating\n", 0);
	else if (philo->status == SLEEPING)
		ft_copy(&output[len], " is sleeping\n", 0);
	else if (philo->status == THINKING)
		ft_copy(&output[len], " is thinking\n", 0);
	else if (philo->status == DEAD)
		ft_copy(&output[len], " died\n", 0);
	pthread_mutex_lock(&philo->times->terminal_lock);
	ft_write_string(output);
	pthread_mutex_unlock(&philo->times->terminal_lock);
	return (0);
}

