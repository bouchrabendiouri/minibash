/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:51:06 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:51:08 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data g_data;

int	cmd_count(t_ast_node *ptr)
{
	static int	count;

	if (ptr->type == CMD)
		count++;
	else
	{
		cmd_count(ptr->content->pipe->right);
		cmd_count(ptr->content->pipe->left);
	}
	return (count);
}

void	ft_wait(void)
{
	int	status;

	status = 0;
	while (1)
	{
		g_data.pid = waitpid(-1, &status, 0);
		if (g_data.pid == -1 && errno == EINTR)
			continue ;
		if (g_data.pid == -1)
			break ;
	}
	if (WIFSIGNALED(status))
	{
		g_data.exit_status = WTERMSIG(status) + 128;
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	// if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	// 	printf("%s: %i\n", g_data.siglist[status], status);
	g_data.which = 0;
}

void	set_g_data(char **env)
{
		(void)env;
		// g_data.env = env;
		// g_data.ev = create_env(env);
		g_data.tree = init_tree(g_data.tree);
		g_data.shell_state = SH_READING;
		g_data.cmd_executing = 0;
}

int	ft_readline(char **line)
{
	*line = readline("[minishell][:)]~> ");
		g_data.shell_state = SH_EXECUTING;
	if (!*line)
	{
		printf("exit\n");
		exit(1);
	}
	if (ft_strcmp(*line, "") == EQUAL || ft_strisspace(*line))
		return (1);
	if (strlen(*line) > 0)
		add_history(*line);
	return (0);
}

void	lunch_program(t_env *env_data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		set_g_data(NULL);
		if (ft_readline(&line))
			continue ;
		g_data.lex = lexer(line);
		if (!syntax_errors(g_data.lex))
		{
			if (parse(&g_data.tree, g_data.lex->head, env_data)
				== EXIT_FAILURE)
				continue ;
			g_data.cmd_executing = 1;
			execute(g_data.tree->root, env_data, -1);
			ft_wait();
			g_data.cmd_executing = 0;
			free_lexer_parser(g_data.lex, g_data.tree);
		}
		else
			free_lexer(g_data.lex);
	}
}
