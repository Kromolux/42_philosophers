/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:45:19 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/29 18:16:05 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_prepare_output(int status, char *output);
static void	ft_choose_color(int status, char *output);

int	ft_philo_status(t_philo *philo, int status)
{
	char	output[42];
	char	*time;
	size_t	len;

	time = ft_long_to_string(ft_get_time_delta(philo->start_time,
				philo->actual_time));
	len = ft_strlen(time);
	ft_choose_color(status, output);
	ft_copy(&output[5], time, 0);
	free(time);
	len = ft_strlen(output);
	output[len] = ' ';
	ft_copy(&output[len + 1], philo->name, 0);
	ft_prepare_output(status, output);
	sem_wait(philo->terminal_sema);
	write(1, output, ft_strlen(output));
	sem_post(philo->terminal_sema);
	return (0);
}

static void	ft_prepare_output(int status, char *output)
{
	size_t	len;

	len = ft_strlen(output);
	if (status == FORK)
		ft_copy(&output[len], " has taken a fork\n", 0);
	else if (status == EATING)
		ft_copy(&output[len], " is eating\n", 0);
	else if (status == SLEEPING)
		ft_copy(&output[len], " is sleeping\n", 0);
	else if (status == THINKING)
		ft_copy(&output[len], " is thinking\n", 0);
	else if (status == DEAD)
		ft_copy(&output[len], " died\n", 0);
	else if (status == DEBUG)
		ft_copy(&output[len], " debug timestamp\n", 0);
	ft_copy(&output[ft_strlen(output)], COLOR_DEFAULT, 0);
}

static void	ft_choose_color(int status, char *output)
{
	if (status == FORK)
		ft_copy(output, COLOR_YELLOW, 0);
	else if (status == EATING)
		ft_copy(output, COLOR_GREEN, 0);
	else if (status == SLEEPING)
		ft_copy(output, COLOR_BLUE, 0);
	else if (status == THINKING)
		ft_copy(output, COLOR_MAGENTA, 0);
	else if (status == DEAD)
		ft_copy(output, COLOR_RED, 0);
	else if (status == DEBUG)
		ft_copy(output, COLOR_BLUE, 0);
	else
		ft_copy(output, COLOR_DEFAULT, 0);
}
