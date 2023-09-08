/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:49:25 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:49:27 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fd(t_cmd *cmd, int fd[2])
{
	if (cmd->fd.in != 0)
	{
		if (dup2(cmd->fd.in, STDIN_FILENO) < 0)
		{
			printf("cmd: %s in dup failed: %s\n",cmd->args[0], strerror(errno));
			exit(1);
		}
		close(fd[1]);
	}
	if (cmd->fd.out != 1)
	{
		if (dup2(cmd->fd.out, STDOUT_FILENO) < 0)
		{
			printf("cmd: %s out dup failed: %s\n", cmd->args[0], strerror(errno));
			exit(1);
		}
		if (cmd->fd.out == fd[1])
			close(fd[0]);
	}
}

void	execute_builtins(t_cmd *cmd, t_env *env_data, int fd[2])
{
	int	in;
	int	out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (cmd->redir && cmd->redir->head)
		exec_redir(cmd->redir, &cmd->fd);
	if (cmd->fd.in == -1)
	{
		g_data.exit_status = 1;
		return ;
	}
	check_fd(cmd, fd);
	ft_which_cmd(cmd, env_data);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}

int	execute_cmd(t_cmd *cmd, t_env *env_data, int fd[2])
{
	char	*cm;
	int		pid;

	signal(SIGQUIT, signal_handler);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		if (cmd->redir && cmd->redir->head)
		{
			exec_redir(cmd->redir, &cmd->fd);
			if (cmd->fd.in == -1)
				exit(1);
		}
		check_fd(cmd, fd);
		cm = find_command(cmd->args[0], env_data);
		if (cm)
			execve(cm, cmd->args, env_data->env);
	}
	return (pid);
}
