/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:49:01 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:49:03 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	t_env_elem	*tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

char *concat_env(t_env_elem *node)
{
	char	*env;
	char	*tmp;

	env = ft_strjoin(node->key, "=");
	tmp = env;
	env = ft_strjoin(env, node->value);
	free(tmp);
	return (env);
}

void update_env_array(t_env *env_data)
{
	int			i;
	t_env_elem	*tmp;

	tmp = env_data->head;
	i = 0;
	while (env_data->env[i])
	{
		free(env_data->env[i]);
		++i;
	}
	free(env_data->env);
	env_data->env = (char**)malloc(sizeof(char*) * (env_data->size + 1));
	if (!env_data->env)
		exit(1);
	i = 0;
	while (tmp)
	{
		env_data->env[i] = concat_env(tmp);
		tmp = tmp->next;
		++i;
	}
	env_data->env[i] = NULL;
}

void	del_env_elem(t_env *env, t_env_elem *elem)
{
	if (elem->next)
		elem->next->prev = elem->prev;
	if (elem->prev)
		elem->prev->next = elem->next;
	env->size--;
	free(elem->key);
	free(elem->value);
	free(elem);
	elem = NULL;
}

void	del_env(t_env *env)
{
	t_env_elem	*tmp;

	tmp = env->head;
	while (tmp)
	{
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = tmp->next;
	}
	free(env);
}

void	print_env_arr(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}

char	**convert_array(t_env *env)
{
	t_env_elem	*tmp;
	char		**arr;
	int			i;

	i = 0;
	tmp = env->head;
	arr = ft_calloc(env->size + 1, sizeof(char *));
	if (arr)
	{
		while (i < env->size)
		{
			char *key = ft_strdup(tmp->key);
			char *value = tmp->value ? ft_strdup(tmp->value) : NULL;

			if (value)
				key = ft_strjoin(key, "=");

			if (value)
				key = ft_strjoin(key, value);

			arr[i] = key;
			i++;

			tmp = tmp->next;

			// N'oubliez pas de libérer la mémoire allouée pour value
			free(value);
		}
		arr[i] = NULL;
	}
	return (arr);
}
