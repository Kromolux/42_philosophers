/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 09:07:50 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/13 14:04:07 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_init_main(t_philo *philo);
//static int	ft_loop(t_philo *philos);
static void	ft_destroy_main(t_philo *philo);
sem_t		*ft_sem_init(char *name, int value);

int	main(int argc, char **argv)
{
	t_philo		philo;

	if (argc != 5 && argc != 6)
		return (ft_error_arguments());
	memset((void *) &philo, 0, sizeof(t_philo));
	if (!ft_check_input(argv) || !ft_get_arguments(&philo, argv))
		return (0);
	ft_init_main(&philo);
	ft_init_processes(&philo);
	if (philo.num_meals > 0)
		pthread_create(&philo.meal_check_thread, NULL, &ft_check_meals,
				(void *) &philo);
	pthread_create(&philo.dead_check_thread, NULL, &ft_check_dead,
				(void *) &philo);
	int	i = 0;
	usleep(100000);
	while (i < philo.num_philos)
	{
		sem_post(philo.dead_sema);
		i++;
	}
	//pthread_create(&philo.life_signal_thread, NULL, &ft_send_life_signal,
	//			(void *) &philo);
	pthread_join(philo.dead_check_thread, NULL);
	pthread_join(philo.meal_check_thread, NULL);
	ft_destroy_main(&philo);
	return (1);
}

static void	ft_init_main(t_philo *philo)
{
	philo->forks_sema = ft_sema_init("forks", philo->num_philos);
	philo->terminal_sema = ft_sema_init("terminal", 1);
	philo->meals_sema = ft_sema_open("meals", 0);
	philo->dead_sema = ft_sema_open("dead", 0);
	philo->status = THINKING;
}

static void	ft_destroy_main(t_philo *philo)
{
	if (philo->all_ate > 0 && philo->dead == 0)
		printf(COLOR_GREEN
			"All Philosophers ate at least %i times. Simulation stopped.\n"
			COLOR_DEFAULT, philo->all_ate);
	else
	{
		printf(COLOR_YELLOW
			"One Philosopher died! Simulation stopped.\n"
			COLOR_DEFAULT);
	}
	sem_close(philo->terminal_sema);
	sem_close(philo->forks_sema);
	sem_close(philo->meals_sema);
	sem_close(philo->dead_sema);
	sem_close(philo->thread_sema);
}

sem_t	*ft_sem_init(char *name, int value)
{
	sem_t	*sema;
	
	sema = sema_open(name, O_CREAT | O_EXCL, 0755, value);
	if (sema != - 1)
		return (sema);
	sem_unlink(name);
	sema = sem_open(name, O_CREAT | O_EXCL, 0755, value);
	return (sema);
}
