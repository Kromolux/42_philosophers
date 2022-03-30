/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 09:07:50 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/30 11:13:32 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_prepare_simulation(t_philo *philo);
static void	ft_destroy_main(t_philo *philo);

int	main(int argc, char **argv)
{
	t_philo		philo;

	if (argc != 5 && argc != 6)
		return (ft_error_arguments());
	memset((void *) &philo, 0, sizeof(t_philo));
	if (!ft_check_input(argv) || !ft_get_arguments(&philo, argv))
		return (0);
	ft_init_main_sema(&philo);
	ft_init_processes(&philo);
	usleep(50000);
	ft_prepare_simulation(&philo);
	sem_wait(philo.dead_sema);
	philo.dead = 1;
	ft_destroy_processes(&philo);
	sem_post(philo.meals_sema);
	sem_post(philo.meals_sema);
	ft_destroy_main(&philo);
	return (1);
}

static void	ft_prepare_simulation(t_philo *philo)
{
	int	i;

	if (philo->num_meals > 0)
		pthread_create(&philo->meal_check_thread, NULL, &ft_check_meals,
			(void *) philo);
	i = 0;
	while (i < philo->num_philos)
	{
		sem_post(philo->start_sema);
		i++;
	}
}

static void	ft_destroy_main(t_philo *philo)
{
	if (philo->num_meals > 0)
		pthread_join(philo->meal_check_thread, NULL);
	if (philo->all_ate > 0)
		printf(COLOR_GREEN
			"All Philosophers ate at least %i times. Simulation stopped.\n"
			COLOR_DEFAULT, philo->num_meals);
	else
	{
		printf(COLOR_YELLOW
			"Philosopher died! Simulation stopped.\n"
			COLOR_DEFAULT);
	}
	ft_close_all_sema(philo);
}
