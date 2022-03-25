/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:45:19 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/18 11:59:50 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_prepare_output(int status, char *output);
static void	ft_choose_color(int status, char *output);
static void	ft_terminal_output(t_philos *philo, char *output);

int	ft_philo_status(t_philos *philo, int status)
{
	char	output[42];
	char	*time;
	size_t	len;

	gettimeofday(&philo->actual_time, NULL);
	time = ft_long_to_string(ft_get_time_delta(philo->start_time,
				philo->actual_time) / 1000);
	len = ft_strlen(time);
	ft_choose_color(status, output);
	ft_copy(&output[5], time, 0);
	free(time);
	len = ft_strlen(output);
	output[len] = ' ';
	ft_copy(&output[len + 1], philo->name, 0);
	ft_prepare_output(status, output);
	ft_terminal_output(philo, output);
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
	else
		ft_copy(output, COLOR_DEFAULT, 0);
}

static void	ft_terminal_output(t_philos *philo, char *output)
{
	pthread_mutex_lock(&philo->times->terminal_lock);
	if (philo->times->terminal != -1)
	{
		write(1, output, ft_strlen(output));
		if (philo->stop == 1)
			philo->times->terminal = -1;
	}
	pthread_mutex_unlock(&philo->times->terminal_lock);
}
