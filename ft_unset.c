/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:50:38 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:50:40 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(char c)
{
	return (c >= 0 && c <= 9);
}

void	remove_env(t_env *env_data, char *key)	
{
	t_env_elem	*tmp;
	t_env_elem	*tmp2;

	tmp = env_data->head;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->key, key))	
		{
			tmp2 = tmp->next;
			tmp->next = tmp2->next;
			free(tmp2->key);
			free(tmp2->value);
			free(tmp2);
			env_data->size--;
			break;
		}
		tmp = tmp->next;
	}
	update_env_array(env_data);
}

void	unset_env(char *args, t_env *env_data)
{
	t_env_elem	*elem;

	elem = NULL;
	if (args && !ft_isalpha(args[0]))
	{
		printf("minishell: unset: `%s`: not a valid identifier\n",
			args);
		g_data.exit_status = EXIT_FAILURE;
	}
	else
	{
		remove_env(env_data, args);
		// elem = search_env_elem(env, args);
		// if (elem)
		// 	del_env_elem(env, elem);
	}
}

int	ft_unset(t_cmd *cmd, t_env *env_data)
{
	int		i;

	i = 1;
	g_data.exit_status = EXIT_SUCCESS;
	while (cmd->args[i])
	{
		unset_env(cmd->args[i], env_data);
		i++;
	}
	return (g_data.exit_status);
}
