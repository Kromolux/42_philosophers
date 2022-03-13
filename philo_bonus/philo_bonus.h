/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 09:04:12 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/13 11:16:55 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <signal.h>
# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define DEAD 4
# define COLOR_DEFAULT "\033[0m"
# define COLOR_RED "\033[31m"
# define COLOR_GREEN "\033[32m"
# define COLOR_YELLOW "\033[33m"
# define COLOR_BLUE "\033[34m"
# define COLOR_MAGENTA "\033[35m"
# define COLOR_WHITE "\033[37m"
# define COLOR_LEN 10

typedef struct s_philo {
	char			*name;
	pid_t			*pid;
	int				myturn;
	struct timeval	start_time;
	struct timeval	life_time;
	struct timeval	action_time;
	struct timeval	actual_time;
	sem_t			*forks_sema;
	sem_t			*terminal_sema;
	sem_t			*meals_sema;
	sem_t			*dead_sema;
	sem_t			*thread_sema;
	long			d_action_time;
	int				has_fork;
	int				status;
	int				meals;
	int				all_ate;
	int				dead;
	int				num_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				num_meals;
	pthread_t		meal_check_thread;
	pthread_t		dead_check_thread;
	pthread_t		life_signal_thread;
}				t_philo;

//ft_error_bonus.c
int			ft_error_arguments(void);
int			ft_error_malloc(char *function, char *variable, size_t size);
int			ft_error_num_philos(void);
int			ft_error_time_die(void);
int			ft_error_create_philos(void);

//ft_string_to_long_bonus.c
long		ft_string_to_long(const char *nptr);

//ft_check_input_bonus.c
int			ft_check_input(char **input);

//ft_get_arguments_bonus.c
int			ft_get_arguments(t_philo *philo, char **input);

//ft_realloc_bonus.c
char		*ft_realloc(char *s1, char *s2, int free_s1, int free_s2);

//ft_copy_bonus.c
size_t		ft_copy(char *dst, char *src, size_t size);

//ft_write_string_bonus.c
int			ft_write_string(char *s);

//ft_long_to_string_bonus.c
char		*ft_long_to_string(long n);

//ft_strlen_bonus.c
size_t		ft_strlen(const char *s);

//ft_init_process_bonus.c
int			ft_init_processes(t_philo *philo);
void		ft_destroy_processes(t_philo *philo);

//ft_philo_process_bonus.c
void		ft_philosopher(t_philo *philo, int i);

//ft_status_bonus.c
int			ft_philo_status(t_philo *philo, int fork);

//ft_time_bonus.c
long		ft_get_time_delta(struct timeval start_time,
				struct timeval actual_time);

//ft_check_meals_bonus.c
void		*ft_check_meals(void *input);
void		*ft_check_dead(void *input);
void		*ft_send_life_signal(void *input);

#endif