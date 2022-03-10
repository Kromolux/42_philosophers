/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 09:04:12 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/10 16:24:01 by rkaufman         ###   ########.fr       */
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
# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define DEAD 4

typedef struct s_loop {
	int				turn;
	struct s_loop	*next;
}				t_loop;

typedef struct s_times {
	struct timeval	start;
	struct timeval	actual;
	struct timeval	interval;
	long			delta;
	int				turn;
	pthread_mutex_t	terminal_lock;
	struct s_loop	*loop;
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
	struct timeval	life_time;
	struct timeval	action_time;
	pthread_mutex_t	*left_fork_lock;
	pthread_mutex_t	right_fork_lock;
	int				*left_fork;
	int				right_fork;
	int				status;
	int				meals;
	t_props			*props;
	t_times			*times;
	
}				t_philos;

//ft_error.c
int			ft_error_arguments(void);
int			ft_error_malloc(char *function, char *variable, size_t size);
int			ft_error_num_philos(void);
int			ft_error_time_die(void);

//ft_string_to_long.c
long		ft_string_to_long(const char *nptr);

//ft_check_input.c
int			ft_check_input(char **input);

//ft_get_arguments.c
int			ft_get_arguments(t_props *props, char **input);

//ft_realloc.c
char		*ft_realloc(char *s1, char *s2, int free_s1, int free_s2);

//ft_copy.c
size_t		ft_copy(char *dst, char *src, size_t size);

//ft_write_string.c
int			ft_write_string(char *s);

//ft_long_to_string.c
char		*ft_long_to_string(long n);

//ft_strlen.c
size_t		ft_strlen(const char *s);

//ft_init_philos.c
t_philos	*ft_init_philos(t_props *props, t_times *times);
void		ft_destroy_philos(t_philos *philos);
void		ft_create_threads(t_philos *philos);

//ft_philo_thread.c
void		*ft_philo_thread(void *input);

//ft_status.c
int			ft_philo_status(t_philos *philo, int fork);

//ft_time.c
long		ft_get_time_delta(struct timeval *start_time, struct timeval *actual_time);

//ft_loop.c
t_loop	*ft_create_new_element(int value);
int		ft_add_element(t_loop **list, t_loop *new_element);
void	ft_delete_list(t_loop **list);
int		ft_create_loop_2(t_loop **list);
int		ft_create_loop_6(t_loop **list);

#endif
