/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 09:07:50 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/29 13:10:47 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_main(t_props *props, t_times *times);
static int	ft_loop(t_philos *philos, t_props *props);
static void	ft_destroy_main(t_times *times, t_props *props);

int	main(int argc, char **argv)
{
	t_times		times;
	t_props		props;
	t_philos	*philos;

	if (argc != 5 && argc != 6)
		return (ft_error_arguments());
	ft_init_main(&props, &times);
	if (!ft_check_input(argv) || !ft_get_arguments(&props, argv))
		return (0);
	philos = ft_init_philos(&props, &times);
	if (!philos)
		return (ft_error_malloc("ft_init_philos", "philos",
				(size_t) sizeof(t_philos) * props.num_philos));
	if (!ft_create_threads(philos))
		return (ft_error_create_philos());
	ft_set_start_time(philos);
	ft_loop(philos, &props);
	ft_destroy_threads(philos);
	ft_destroy_main(&times, &props);
	return (1);
}

static void	ft_init_main(t_props *props, t_times *times)
{
	memset((void *) props, 0, sizeof(t_props));
	memset((void *) times, 0, sizeof(t_times));
	pthread_mutex_init(&times->terminal_lock, NULL);
	pthread_mutex_init(&times->meal_lock, NULL);
	pthread_mutex_init(&props->alibi_left_lock, NULL);
}

static int	ft_loop(t_philos *philos, t_props *props)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < props->num_philos)
		{
			pthread_mutex_lock(&philos[i].thread_lock);
			if (philos[i].stop == 1)
			{
				pthread_mutex_unlock(&philos[i].thread_lock);
				return (0);
			}
			pthread_mutex_unlock(&philos[i].thread_lock);
			i++;
		}
		if (ft_check_meals(philos, props))
			return (0);
	}
	return (0);
}

static void	ft_destroy_main(t_times *times, t_props *props)
{
	if (times->all_ate > 0)
		printf(COLOR_GREEN
			"All Philosophers ate at least %i times. Simulation stopped.\n"
			COLOR_DEFAULT, times->all_ate);
	else
		printf(COLOR_YELLOW
			"One Philosopher died! Simulation stopped.\n"
			COLOR_DEFAULT);
	pthread_mutex_destroy(&times->terminal_lock);
	pthread_mutex_destroy(&times->meal_lock);
	pthread_mutex_destroy(&props->alibi_left_lock);
}
