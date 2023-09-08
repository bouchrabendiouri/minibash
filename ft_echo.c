/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:49:59 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:50:01 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_opt(char *opt)
{
	int	i;

	i = 1;
	if (opt[0] != '-')
		return (0);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd, t_env *env_data)
{
	int i;
	int no_newline;
	char *arg;
	char *var_name;
	char *var_value;

	i = 1;
	no_newline = 0;
	if (cmd->args[1] && is_opt(cmd->args[1]))
	{
		if (cmd->args[1][1] == 'n')
		{
			no_newline = 1;
			i++;
		}
	}
	while (cmd->args[i])
	{
		arg = cmd->args[i];
		if (arg[0] == '$')
		{
			var_name = arg + 1;
			var_value = expand_env(var_name, env_data);
			if (var_name)
				write(STDOUT_FILENO, var_value, ft_strlen(var_value));
		}
		else
		{
			write(STDOUT_FILENO, arg, ft_strlen(arg));
		}
		if (cmd->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!no_newline)
	write(STDOUT_FILENO, "\n", 1);
	g_data.exit_status = EXIT_SUCCESS;
	return(EXIT_SUCCESS);
}