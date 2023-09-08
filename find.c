/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:49:40 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:49:42 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_slash_dot(char *cmd, t_env *env_data)
{
	char	*cmd_path;

	if (cmd[0] == '/')
	{
		if (opendir(cmd) != NULL)
			printf("minishell: %s: is a directory\n", cmd);
		else if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			printf("minishell: %s: No such file or directory\n", cmd);
	}
	else if (cmd[0] == '.')
	{
		cmd_path = ft_join_dir(search_env_var("PWD", env_data), cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd);
		else
			printf("minishell: %s: No such file or directory\n", cmd);
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *env_data)
{
	char	**paths;
	char	*path;
	char	*cmd_path;
	int		i;

	i = 0;
	path = search_env_var("PATH", env_data);
	paths = ft_split(path, ":");
	if (!paths)
		return (NULL);
	cmd_path = ft_strdup("");
	if (!cmd_path)
		return (NULL);
	while (paths[i])
	{
		cmd_path = ft_join_dir(paths[i], cmd);
		if (cmd_path)
		{
			if (access(cmd_path, F_OK) == 0)
				return (cmd_path);
			i++;
			free(cmd_path);
		}
	}
	printf("minishell: %s: command not found\n", cmd);
	return (NULL);
}

char	*find_command(char *cmd, t_env *env_data)
{
	char	*cmd_path;

	if (cmd[0] == '/' || cmd[0] == '.')
		cmd_path = find_slash_dot(cmd, env_data);
	else
		cmd_path = find_path(cmd, env_data);
	if (cmd_path)
		return (cmd_path);
	exit(EXIT_FAILURE);
	return (NULL);
}

int	*find_right_left(t_ast_node *ptr)
{
	return (&ptr->content->pipe->right->content-> \
		pipe->left->content->cmd->fd.out);
}
