/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 09:04:12 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/29 18:28:14 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <signal.h>
# define FORK 0
# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define DEAD 4
# define DEBUG 5
# define COLOR_DEFAULT "\033[0m"
# define COLOR_RED "\033[31m"
# define COLOR_GREEN "\033[32m"
# define COLOR_YELLOW "\033[33m"
# define COLOR_BLUE "\033[34m"
# define COLOR_MAGENTA "\033[35m"
# define COLOR_CYAN "\033[36m"
# define COLOR_WHITE "\033[37m"
# define COLOR_LEN 10

typedef struct s_philo {
	char			name[4];
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
	sem_t			*start_sema;
	sem_t			*thread_sema;
	sem_t			*life_sema;
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
	pthread_t		life_check_thread;
}				t_philo;

//ft_error_bonus.c
int			ft_error_arguments(void);
int			ft_error_malloc(char *function, char *variable, size_t size);
int			ft_error_num_philos(void);
int			ft_error_time_die(void);
int			ft_error_create_philos(void);

//ft_semaphore_bonus.c
sem_t		*ft_sema_init(char *name, int value);
void		ft_init_main_sema(t_philo *philo);
void		ft_close_all_sema(t_philo *philo);

//ft_check_input_bonus.c
int			ft_check_input(char **input);

//ft_get_arguments_bonus.c
int			ft_get_arguments(t_philo *philo, char **input);

//ft_utils_bonus.c
long		ft_get_time_delta(struct timeval start_time,
				struct timeval actual_time);
size_t		ft_strlen(const char *s);
size_t		ft_copy(char *dst, char *src, size_t size);
char		*ft_realloc(char *s1, char *s2, int free_s1, int free_s2);

//ft_string_utils_bonus.c
char		*ft_long_to_string(long n);
long		ft_string_to_long(const char *nptr);

//ft_init_process_bonus.c
int			ft_init_processes(t_philo *philo);
void		ft_destroy_processes(t_philo *philo);

//ft_philo_process_bonus.c
void		ft_philosopher(t_philo *philo, int i);

//ft_philo_process_utils_bonus.c
void		ft_prepare_philo(t_philo *philo, int i);
int			ft_dead_with_fork(t_philo *philo);

//ft_status_bonus.c
int			ft_philo_status(t_philo *philo, int status);

//ft_check_meals_bonus.c
void		*ft_check_meals(void *input);

//ft_philo_thread_bonus.c
void		*ft_check_life_time(void *input);

#endif
