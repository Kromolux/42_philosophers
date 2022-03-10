/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:28:23 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/10 17:09:40 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_loop	*ft_create_new_element(int value)
{
	t_loop	*new_element;

	new_element = (t_loop *) malloc(sizeof(t_loop));
	if (!new_element)
	{
		ft_error_malloc("ft_create_new_element", "new_element", sizeof(t_loop));
		return (NULL);
	}
	memset((void *) new_element, 0, sizeof(t_loop));
	new_element->turn = value;
	return (new_element);
}

int	ft_add_element(t_loop **list, t_loop *new_element)
{
	if (!*list)
	{
		*list = new_element;
		return (0);
	}
	if (!list || !new_element)
		return (-1);
	while ((*list)->next)
	{
		*list = (*list)->next;
	}
	(*list)->next = new_element;
	return (0);
}

void	ft_delete_list(t_loop **list)
{
	t_loop	*tmp;
	int		i;
	int		size;

	if ((*list)->turn == 0)
		size = 2;
	else
		size = 6;
	i = 0;
	while (i < size)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		i++;
	}
	list = NULL;
}

int	ft_create_loop_2(t_loop **list)
{
	ft_add_element(list, ft_create_new_element(0));
	ft_add_element(list, ft_create_new_element(1));
	(*list)->next->next = *list;
	return (0);
}

int	ft_create_loop_6(t_loop **list)
{
	t_loop	*tmp;
	printf("entered loop 6\n");
	ft_add_element(list, ft_create_new_element(3));
	ft_add_element(list, ft_create_new_element(0));
	ft_add_element(list, ft_create_new_element(1));
	ft_add_element(list, ft_create_new_element(2));
	ft_add_element(list, ft_create_new_element(0));
	ft_add_element(list, ft_create_new_element(1));
	tmp = *list;
	printf("all elements created\n");
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = *list;
	return (0);
}
