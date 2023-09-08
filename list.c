/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:51:00 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:51:03 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(t_list *list)
{
	return (list->head == NULL);
}

t_list	*init_list(t_list *list)
{
	list = ft_calloc(sizeof(t_list), 1);
	if (!list)
		return (NULL);
	return (list);
}

t_elem	*new_elem(char *content, int len, enum e_token type, enum e_state state)
{
	t_elem	*elem;
	char	*cont;

	elem = ft_calloc(sizeof(t_elem), 1);
	if (!elem)
		return (NULL);
	cont = ft_strndup(content, len);
	if (!cont)
		return (NULL);
	elem->content = cont;
	elem->len = len;
	elem->type = type;
	elem->state = state;
	return (elem);
}

void	add_tail(t_list *list, t_elem *new)
{
	if (is_empty(list))
		list->head = new;
	else
	{
		list->tail->next = new;
		new->prev = list->tail;
	}
	list->tail = new;
	list->size++;
}

void	free_list(t_list *list)
{
	t_elem	*tmp;
	t_elem	*next_tmp;

	tmp = list->head;
	while (tmp)
	{
		free(tmp->content);
		next_tmp = tmp->next;
		free(tmp);
		tmp = next_tmp;
	}
	free(list);
}
