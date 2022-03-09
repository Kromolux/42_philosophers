/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:33:55 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/05 10:58:49 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_number(int i, char c1, char c2);
static int	ft_valid_number(char *argv);

int	ft_check_input(char **input)
{
	int	i_row;

	i_row = 1;
	while (input[i_row])
	{
		if (!ft_valid_number(input[i_row]))
		{
			printf("Error! Invalid number [%s] in arguments input[%i] by"
				" function ft_check_input\n", input[i_row], i_row);
			return (0);
		}
		i_row++;
	}
	return (1);
}

static int	ft_valid_number(char *argv)
{
	int		i;
	int		i_arg;

	i = 0;
	i_arg = 0;
	while (argv[i])
	{
		if (argv[i] == ' ')
		{
			while (argv[i] == ' ')
				i++;
			i_arg = 0;
		}
		if (argv[i] < '0' || argv[i] > '9')
		{
			if (!ft_check_number(i_arg, argv[i], argv[i + 1]))
				return (0);
		}
		i_arg++;
		i++;
	}
	return (1);
}

static int	ft_check_number(int i, char c1, char c2)
{
	if (i > 0 || (c1 != '+') || c2 < '0' || c2 > '9')
		return (0);
	return (1);
}
