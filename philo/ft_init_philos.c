/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:23:04 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/10 16:57:28 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*ft_init_philos(t_props *props, t_times *times)
{
	int	i;
	t_philos	*philos;

	i = 0;
	philos = (t_philos *) malloc(sizeof(t_philos) * props->num_philos);
	if (!philos)
		return (NULL);
	memset((void *) philos, 0, sizeof(t_philos) * props->num_philos);
	while (i < props->num_philos)
	{
		philos[i].name = ft_long_to_string((long) i + 1);
		philos[i].myturn = i % 2;
		pthread_mutex_init(&philos[i].right_fork_lock, NULL);
		philos[i].right_fork = 1;
		philos[i].status = THINKING;
		philos[i].props = props;
		philos[i].times = times;
		i++;
	}
	if (props->num_philos > 1)
	{
		if (philos[props->num_philos - 1].myturn == philos[0].myturn)
		{
			philos[props->num_philos - 1].myturn = 2;
			philos[0].myturn = 3;
			ft_create_loop_6(&times->loop);
		}
		else
		{
			ft_create_loop_2(&times->loop);
		}
		i = 1;
		philos[0].left_fork = &philos[props->num_philos - 1].right_fork;
		philos[0].left_fork_lock = &philos[props->num_philos - 1].right_fork_lock;
		while (i < props->num_philos)
		{
			philos[i].left_fork = &philos[i - 1].right_fork;
			philos[i].left_fork_lock = &philos[i - 1].right_fork_lock;
			i++;
		}
	}
	return (philos);
}

void	ft_destroy_philos(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->props->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philos->props->num_philos)
	{
		pthread_mutex_destroy(&philos[i].right_fork_lock);
		free(philos[i].name);
		i++;
	}
	free(philos);
}

void	ft_create_threads(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->props->num_philos)
	{
		pthread_create(&philos[i].thread, NULL, &ft_philo_thread, (void *) &philos[i]);
		i++;
	}
}
