/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:50:07 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:50:09 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_env *env_data)
{
	int	i;

	i = 0;
	if (!cmd->args[1])
	{
		while (env_data->env[i])
		{
			if (ft_strchr(env_data->env[i], '=') != -1)
				printf("%s\n", env_data->env[i]);
			i++;
		}
	}
	else
	{
		g_data.exit_status = EXIT_FAILURE;
		return (ft_perror("minishell: env: Too many arguments.", NULL));
	}
	return (EXIT_SUCCESS);
}
