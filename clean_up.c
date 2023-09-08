/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:15:38 by nolahmar          #+#    #+#             */
/*   Updated: 2023/08/23 10:15:40 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_list *lexer)
{
	free_list(lexer);
}

void	free_parser(t_ast *tree)
{
	free_tree(tree->root);
	free(tree);
}

void	free_lexer_parser(t_list *lexer, t_ast *tree)
{
	free_lexer(lexer);
	free_parser(tree);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		free(cmd->args[i++]);
	free(cmd->args);
	free_redir_list(cmd->redir);
	free(cmd);
}

void	free_2d(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
}
