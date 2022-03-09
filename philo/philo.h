/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 09:04:12 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/05 11:41:51 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_props {
	int			num_philos;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	int			num_meals;
}				t_props;

//ft_error.c
int		ft_error_arguments(void);
int		ft_error_malloc(char *function, char *variable, size_t size);
int		ft_error_num_philos(void);
int		ft_error_time_die(void);

//ft_string_to_long.c
long	ft_string_to_long(const char *nptr);

//ft_check_input.c
int		ft_check_input(char **input);

//ft_get_arguments.c
int		ft_get_arguments(t_props *props, char **input);

//ft_realloc.c
char	*ft_realloc(char *s1, char *s2, int free_s1, int free_s2);

//ft_copy.c
size_t	ft_copy(char *dst, char *src, size_t size);

//ft_write_string.c
int		ft_write_string(char *s);

//ft_long_to_string.c
char	*ft_long_to_string(long n);

//ft_strlen.c
size_t	ft_strlen(const char *s);

#endif
