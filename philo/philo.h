/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 09:04:12 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/18 12:16:49 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# define FORK 0
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

typedef struct s_times {
	struct timeval	start;
	int				all_ate;
	int				terminal;
	pthread_mutex_t	terminal_lock;
	pthread_mutex_t	meal_lock;
}				t_times;

typedef struct s_props {
	int				num_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				num_meals;
}				t_props;

typedef struct s_philos {
	pthread_t		thread;
	char			*name;
	int				myturn;
	struct timeval	start_time;
	struct timeval	life_time;
	struct timeval	action_time;
	struct timeval	actual_time;
	long			d_action_time;
	pthread_mutex_t	*left_fork_lock;
	pthread_mutex_t	right_fork_lock;
	pthread_mutex_t	thread_lock;
	int				right_fork;
	int				has_right_fork;
	int				*left_fork;
	int				has_left_fork;
	int				status;
	int				stop;
	int				meals;
	t_props			props;
	t_times			*times;
}				t_philos;

//ft_error.c
int			ft_error_arguments(void);
int			ft_error_malloc(char *function, char *variable, size_t size);
int			ft_error_num_philos(void);
int			ft_error_time_die(void);
int			ft_error_create_philos(void);

//ft_check_input.c
int			ft_check_input(char **input);

//ft_get_arguments.c
int			ft_get_arguments(t_props *props, char **input);

//ft_utils.c
long		ft_get_time_delta(struct timeval start_time,
				struct timeval actual_time);
size_t		ft_strlen(const char *s);
size_t		ft_copy(char *dst, char *src, size_t size);
char		*ft_realloc(char *s1, char *s2, int free_s1, int free_s2);

//ft_string_utils.c
char		*ft_long_to_string(long n);
long		ft_string_to_long(const char *nptr);

//ft_init_philos.c
t_philos	*ft_init_philos(t_props *props, t_times *times);
void		ft_destroy_threads(t_philos *philos);
int			ft_create_threads(t_philos *philos);

//ft_philo_thread.c
void		*ft_philo_thread(void *input);

//ft_philo_thread1.c
void		ft_check_life_time(t_philos *philo);
int			ft_check_meals(t_philos *philos, t_props *props);

//ft_status.c
int			ft_philo_status(t_philos *philo, int fork);

#endif
