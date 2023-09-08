/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:49:32 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:49:34 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(char *cmd)
{
	if (cmd && (ft_strcmp(cmd, "export") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "unset") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "pwd") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "exit") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "cd") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "env") == EQUAL))
		return (1);
	else if (cmd && (ft_strcmp(cmd, "echo") == EQUAL))
		return (1);
	return (0);
}

void	ft_which_cmd(t_cmd *cmd, t_env *env_data)
{
	if (cmd->args[0] && (ft_strcmp(cmd->args[0], "export") == EQUAL))
		ft_export(env_data, cmd);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "unset") == EQUAL))
		ft_unset(cmd, env_data);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "pwd") == EQUAL))
		ft_pwd(cmd);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "exit") == EQUAL))
		ft_exit(cmd, env_data);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "cd") == EQUAL))
		ft_cd(cmd, env_data);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "env") == EQUAL))
		ft_env(cmd, env_data);
	else if (cmd->args[0] && (ft_strcmp(cmd->args[0], "echo") == EQUAL))
		ft_echo(cmd, env_data);
}

void	choose_execution(t_cmd *cmd, t_env *env_data, int fd[2])
{
	if (check_builtins(cmd->args[0]) == 1)
		execute_builtins(cmd, env_data, fd);
	else
		execute_cmd(cmd, env_data, fd);
}

int		root_is_cmd(t_ast_node *root, t_env *env_data, int input_pipe)
{
	int fd[2];

	if (input_pipe == -1 && root->type == CMD)
	{
		choose_execution(root->content->cmd, env_data, fd);
		return 1;
	}
	return 0;
}

void	multi_pipe_exec_left(t_ast_node *root, t_env *env_data, int input_pipe, int fd[2])
{
	root->content->pipe->left->content->cmd->fd.out = input_pipe;
	root->content->pipe->left->content->cmd->fd.in = fd[0];
	choose_execution(root->content->pipe->left->content->cmd, env_data, fd);
	close(input_pipe);
	close(fd[0]);
}

void	multi_pipe_exec_right(t_ast_node *root, t_env *env_data, int input_pipe, int fd[2])
{
	root->content->pipe->right->content->cmd->fd.out = fd[1];
	choose_execution(root->content->pipe->right->content->cmd, env_data, fd);
	close(fd[1]);
}

void	single_or_multi_pipe_left_exec(t_ast_node *root, t_env *env_data, int input_pipe, int fd[2])
{
	root->content->pipe->left->content->cmd->fd.in = fd[0];
	choose_execution(root->content->pipe->left->content->cmd, env_data, fd);
	close(fd[0]);
}

void	single_pipe_right_exec(t_ast_node *root, t_env *env_data, int input_pipe, int fd[2])
{
	root->content->pipe->right->content->cmd->fd.out = fd[1];
	choose_execution(root->content->pipe->right->content->cmd, env_data, fd);
	close(fd[1]);
}

void	execute(t_ast_node *root, t_env *env_data, int input_pipe)
{
	int			fd[2];

	if (root_is_cmd(root, env_data, input_pipe))
		return;
	if (pipe(fd) < 0) return;
	if (input_pipe != -1)
	{
		multi_pipe_exec_left(root, env_data, input_pipe, fd);
		if (root->content->pipe->right->type == PIPE)
		{
			execute(root->content->pipe->right, env_data, fd[1]);
			return;
		}
		multi_pipe_exec_right(root, env_data, input_pipe, fd);
		return;
	}
	single_or_multi_pipe_left_exec(root, env_data, input_pipe, fd);
	if (root->content->pipe->right->type == PIPE)
	{
		execute(root->content->pipe->right, env_data, fd[1]);
		return;
	}
	single_pipe_right_exec(root, env_data, input_pipe, fd);
}
