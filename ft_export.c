/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:50:20 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:50:22 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_elem *get_key(t_env_elem *head, char *key)
{
	t_env_elem *tmp;

	tmp = head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return NULL;
}

void handle_env(t_env *env_data, t_cmd *cmd) {
	char		*key;
	char		*value;
	t_env_elem 	*env_elem;
    int			i;
	int			index;

	i = 0;
    while (cmd->args[i])
	{
		index = ft_strchr(cmd->args[i], '=');
		if (index == -1)
		{
			++i;
			continue;
		}
		key = ft_substr(cmd->args[i], 0, index);
		value = ft_substr(cmd->args[i], index + 1, ft_strlen(cmd->args[i]) - index);
		env_elem = get_key(env_data->head, key);
		if (env_elem)
		{
			free(key);
			env_elem->value = value;
		}
		else
			add_env_elem(env_data, new_env_elem(cmd->args[i]));
		++i;
    }
	update_env_array(env_data);
}

int	ft_export(t_env *env_data, t_cmd *cmd)
{
	if (!cmd->args[1])
		print_sorted_env(env_data);
	else
	{
		// '_' is a special case
		if (!ft_isalpha(cmd->args[1][0]))
			return (ft_puterr(cmd->args[0],
					cmd->args[1], "not a valid identifier", EXIT_FAILURE));
		handle_env(env_data, cmd);
	}
	g_data.exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);

}
