/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:51:12 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:51:14 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->exit_status = 0;
	data->which = 0;
	data->pid = 0;
	data->tree = NULL;
	data->ev = NULL;
	data->alloc = 0;
}

void	signal_handler(int sig)
{
	if (sig == SIGQUIT)
		printf("Quit\n");
	if (sig == SIGINT && !g_data.cmd_executing)
		printf("\n[minishell][:)]~> ");
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	t_env *env_data;

	(void)av;
	if (ac != 1 || !*env)
		return (1);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	env_data = create_env(env);
	init_data(&g_data);
	lunch_program(env_data);
	return (0);
}
