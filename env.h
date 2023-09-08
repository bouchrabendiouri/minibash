/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:49:08 by nolahmar          #+#    #+#             */
/*   Updated: 2023/09/08 11:49:10 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_elem
{
	char				*key;
	char				*value;
	struct s_env_elem	*next;
	struct s_env_elem	*prev;
}	t_env_elem;

typedef struct s_env
{
	t_env_elem			*head;
	char				**env;
	int					size;
}	t_env;

t_env		*init_env(t_env *env);
t_env_elem	*new_env_elem(char *line);
void		add_env_elem(t_env *env, t_env_elem *elem);
t_env		*create_env(char **tab);

void		print_env(t_env *env);
char		**convert_array(t_env *env);
void		del_env_elem(t_env *env, t_env_elem *elem);
void		del_env(t_env *env);
void		print_env_arr(char **env);

char		*get_env_value(char *key, t_env *env);
t_env_elem	*search_env_elem(t_env *env, char *key);
char		*search_env_var(char *key, t_env *env);
char		*expand_env(char *line, t_env *env);
char		*get_expanded_value(char **line, t_env *env);
void		update_env_array(t_env *env_data);

#endif
