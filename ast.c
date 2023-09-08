/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:52:07 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:52:09 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast_node(t_ast_node *cmd)
{
	int	i;

	i = 0;
	while (cmd->content->cmd->args[i])
	{
		printf("command arg[%i]: %s\n", i, cmd->content->cmd->args[i]);
		i++;
	}
	print_redir_list(cmd->content->cmd->redir);
	printf("fd->in: %d, fd->out: %d\n", cmd->content->cmd->fd.in,
		cmd->content->cmd->fd.out);
}

void	print_tree(t_ast_node *ptr, char **env)
{
	static int c;
	printf("call %d\n", c + 1);
	c++;
	if (ptr->type == CMD)
	{
		printf("\n------------------------\n");
		printf("CMD Node\n");
		print_ast_node(ptr);
	}
	else if (ptr->type == PIPE)
	{
		printf("\n------------------------\n");
		printf("PIPE Node\n");
		print_tree(ptr->content->pipe->right, env);
		print_tree(ptr->content->pipe->left, env);
	}
}

t_ast	*init_tree(t_ast *tree)
{
	tree = malloc(sizeof(t_ast));
	if (!tree)
		return (NULL);
	tree->root = NULL;
	return (tree);
}

t_ast_node	*create_cmd_node(char **args, char **env, t_redir_list *redir)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->content = malloc(sizeof(t_union));
	node->content->cmd = malloc(sizeof(t_cmd));
	if (!node || !node->content || !node->content->cmd)
		return (NULL);
	node->type = CMD;
	node->content->cmd->args = args;
	node->content->cmd->env = env;
	node->content->cmd->redir = redir;
	node->content->cmd->fd.in = 0;
	node->content->cmd->fd.out = 1;
	return (node);
}

void	free_tree(t_ast_node *node)
{
	if (node->type == CMD)
	{
		free_cmd(node->content->cmd);
		free(node->content);
		free(node);
	}
	else if (node->type == PIPE)
	{
		free_tree(node->content->pipe->right);
		free_tree(node->content->pipe->left);
		free(node->content->pipe);
		free(node->content);
		free(node);
	}
}
