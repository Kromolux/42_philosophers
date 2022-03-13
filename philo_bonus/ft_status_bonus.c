/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:45:19 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/13 10:52:54 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_prepare_output(t_philo *philo, int fork, char *output);
static void	ft_choose_color(int status, int fork, char *output);

int	ft_philo_status(t_philo *philo, int fork)
{
	char	*output;
	char	*time;
	size_t	len;

	time = ft_long_to_string(ft_get_time_delta(philo->start_time,
				philo->actual_time) / 1000);
	len = ft_strlen(time);
	output = (char *) malloc(len + ft_strlen(philo->name) + 23 + COLOR_LEN);
	if (!output)
		return (ft_error_malloc("ft_philo_status", "output",
				(len + ft_strlen(philo->name) + 23 + COLOR_LEN)));
	ft_choose_color(philo->status, fork, output);
	ft_copy(&output[5], time, 0);
	free(time);
	len = ft_strlen(output);
	output[len] = ' ';
	ft_copy(&output[len + 1], philo->name, 0);
	ft_prepare_output(philo, fork, output);
	sem_wait(philo->terminal_sema);
	ft_write_string(output);
	sem_post(philo->terminal_sema);
	if (philo->status == DEAD)
		sem_post(philo->dead_sema);
	return (0);
}

static void	ft_prepare_output(t_philo *philo, int fork, char *output)
{
	size_t	len;

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
	ft_copy(&output[ft_strlen(output)], COLOR_DEFAULT, 0);
}

static void	ft_choose_color(int status, int fork, char *output)
{
	if (fork == 1)
		ft_copy(output, COLOR_YELLOW, 0);
	else if (status == EATING)
		ft_copy(output, COLOR_GREEN, 0);
	else if (status == SLEEPING)
		ft_copy(output, COLOR_BLUE, 0);
	else if (status == THINKING)
		ft_copy(output, COLOR_MAGENTA, 0);
	else if (status == DEAD)
		ft_copy(output, COLOR_RED, 0);
	else
		ft_copy(output, COLOR_DEFAULT, 0);
}
