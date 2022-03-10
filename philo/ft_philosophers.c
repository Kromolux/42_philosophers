/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 09:07:50 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/10 17:08:13 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ft_philos_had_meals(t_philos *philos);
static void	ft_init_main(t_props *props, t_times *times, int *i);
static void	ft_destroy_main(t_times *times);

int	main(int argc, char **argv)
{
	int			i;
	t_times		times;
	t_props		props;
	t_philos	*philos;

	if (argc != 5 && argc != 6)
		return (ft_error_arguments());
	ft_init_main(&props, &times, &i);
	if (!ft_check_input(argv) || !ft_get_arguments(&props, argv))
		return (-1);
	philos = ft_init_philos(&props, &times);
	if (!philos)
		return (ft_error_malloc("ft_init_philos", "philos",
			(size_t) sizeof(t_philos) * props.num_philos));
	//printf("num_philos=%i\ntime_die=%lu\ntime_eat=%lu\ntime_sleep=%lu\nnum_meals=%i\n", props.num_philos, props.time_die, props.time_eat, props.time_sleep, props.num_meals);
	gettimeofday(&times.start, NULL);
	times.interval.tv_sec = times.start.tv_sec;
	times.interval.tv_usec = times.start.tv_usec;
	times.turn = 0;
	i = 0;
	while (i < props.num_philos)
	{
		philos[i].life_time.tv_sec = times.start.tv_sec;
		philos[i].life_time.tv_usec = times.start.tv_usec;
		//printf("philo=%i turn=%i\n", i + 1, philos[i].myturn);
		i++;
	}
	//printf("turn %i\n", times.turn);
	ft_create_threads(philos);
	i = 0;
	while (philos->status != DEAD && props.num_meals != 0 && !ft_philos_had_meals(philos))
	{
		gettimeofday(&times.actual, NULL);
		times.delta = ft_get_time_delta(&times.start, &times.actual);
		if (ft_get_time_delta(&times.interval, &times.actual) >= (props.time_eat))
		{
			times.loop = times.loop->next;
			times.interval.tv_sec = times.actual.tv_sec;
			times.interval.tv_usec = times.actual.tv_usec;
		}
		if ((times.loop->turn == 3 && philos[0].right_fork == 0)
			|| (times.loop->turn == 2 && *philos[0].left_fork == 0))
			times.loop = times.loop->next;
		usleep(1);
	}
	ft_destroy_philos(philos);
	ft_destroy_main(&times);
	return (0);
}

int	ft_philos_had_meals(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->props->num_philos)
	{
		if (philos[i].meals < philos->props->num_meals)
			return (0);
		i++;
	}
	return (1);
}

static void	ft_init_main(t_props *props, t_times *times, int *i)
{
	i = 0;
	memset((void *) props, 0, sizeof(t_props));
	memset((void *) times, 0, sizeof(t_times));
	pthread_mutex_init(&times->terminal_lock, NULL);
}

static void	ft_destroy_main(t_times *times)
{
	ft_delete_list(&times->loop);
	pthread_mutex_destroy(&times->terminal_lock);
}
