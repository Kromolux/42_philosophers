/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 09:07:50 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/05 11:43:14 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int				i;
	struct timeval	start_time;
	struct timeval	end_time;
	long			time;
	t_props			props;

	i = 0;
	if (argc != 5 && argc != 6)
		return (ft_error_arguments());
	if (!ft_check_input(argv) || !ft_get_arguments(&props, argv))
		return (-1);
	printf("num_philos=%i\ntime_die=%lu\ntime_eat=%lu\ntime_sleep=%lu\nnum_meals=%i\n", props.num_philos, props.time_die, props.time_eat, props.time_sleep, props.num_meals);
	gettimeofday(&start_time, NULL);
	//gettimeofday(&end_time, NULL);
	//printf("executiontime=%lu %lu %lu %lu\n", start_time.tv_sec, start_time.tv_usec, end_time.tv_sec, end_time.tv_usec);
	//printf("result= %lu %lu\n", end_time.tv_sec - start_time.tv_sec, end_time.tv_usec - start_time.tv_usec);
	i = 0;
	while (i < props.num_meals)
	{
		gettimeofday(&end_time, NULL);
		time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
		if (time >= props.time_eat)
		{
			ft_write_string(ft_realloc(ft_long_to_string(time), "\n", 1, 0));
			//printf("result= %lu\n", time);
			//printf("executiontime=%lu %lu %lu %lu\n", start_time.tv_sec, start_time.tv_usec, end_time.tv_sec, end_time.tv_usec);
			start_time.tv_sec = end_time.tv_sec;
			start_time.tv_usec = end_time.tv_usec;
			i++;
		}
		usleep(1);
	}
	return (0);
}
