/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:30:32 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/12 09:10:41 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_realloc(char *s1, char *s2, int free_s1, int free_s2)
{
	ssize_t		s1_len;
	char		*output;

	s1_len = ft_strlen(s1);
	output = (char *)malloc(s1_len + ft_strlen(s2) + 1);
	if (!output)
		return (NULL);
	ft_copy(output, s1, 0);
	ft_copy(&output[s1_len], s2, 0);
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (output);
}
