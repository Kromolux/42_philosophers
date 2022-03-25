/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:23:04 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/18 12:25:54 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_assign_values(t_props *props, t_times *times, t_philos *philos);

t_philos	*ft_init_philos(t_props *props, t_times *times)
{
	t_philos	*philos;
	int			i;

	i = 0;
	philos = (t_philos *) malloc(sizeof(t_philos) * props->num_philos);
	if (!philos)
		return (NULL);
	memset((void *) philos, 0, sizeof(t_philos) * props->num_philos);
	ft_assign_values(props, times, philos);
	if (props->num_philos > 1)
	{
		i = 1;
		philos[0].left_fork_lock
			= &philos[props->num_philos - 1].right_fork_lock;
		philos[0].left_fork
			= &philos[props->num_philos - 1].right_fork;
		while (i < props->num_philos)
		{
			philos[i].left_fork_lock = &philos[i - 1].right_fork_lock;
			philos[i].left_fork = &philos[i - 1].right_fork;
			i++;
		}
	}
	return (philos);
}

static void	ft_assign_values(t_props *props, t_times *times, t_philos *philos)
{
	int	i;

	i = 0;
	while (i < props->num_philos)
	{
		philos[i].name = ft_long_to_string((long) i + 1);
		if ((props->num_philos % 2) == 0)
			philos[i].myturn = i % 2;
		else
			philos[i].myturn = i % 3;
		pthread_mutex_init(&philos[i].right_fork_lock, NULL);
		pthread_mutex_init(&philos[i].thread_lock, NULL);
		philos[i].right_fork = 1;
		philos[i].status = THINKING;
		philos[i].props = *props;
		philos[i].times = times;
		i++;
	}
}

int	ft_create_threads(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->props.num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &ft_philo_thread,
				(void *) &philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_destroy_threads(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->props.num_philos)
	{
		pthread_mutex_lock(&philos[i].thread_lock);
		philos[i].stop = 1;
		pthread_mutex_unlock(&philos[i].thread_lock);
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philos->props.num_philos)
	{
		pthread_mutex_destroy(&philos[i].right_fork_lock);
		pthread_mutex_destroy(&philos[i].thread_lock);
		free(philos[i].name);
		i++;
	}
	free(philos);
}
