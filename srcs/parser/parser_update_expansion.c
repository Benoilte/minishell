/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:13:10 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/24 12:58:50 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	get_dollar_sign(t_bash *bash, t_list **recast)
{
	char	*dollar;

	dollar = ft_strdup("$");
	if (!dollar)
	{
		ft_lstclear(recast, &free_content);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	add_back_recast(bash, recast, dollar);
}

void	get_last_cmd_exit_status(t_bash *bash, t_list **recast, int *i)
{
	char	*last_cmd_exit_status;

	*i += 1;
	last_cmd_exit_status = ft_itoa(bash->exit_code);
	if (!last_cmd_exit_status)
	{
		ft_lstclear(recast, &free_content);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	add_back_recast(bash, recast, last_cmd_exit_status);
}

// pgrep minishell
void	get_process_id(t_bash *bash, t_list **recast, int *i)
{
	char	*process_id;

	*i += 1;
	process_id = ft_strdup("0");
	if (!process_id)
	{
		ft_lstclear(recast, &free_content);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	add_back_recast(bash, recast, process_id);
}

void	get_minishell_name(t_bash *bash, t_list **recast, int *i)
{
	char	*minishell_name;

	*i += 1;
	minishell_name = ft_strdup("minishell");
	if (!minishell_name)
	{
		ft_lstclear(recast, &free_content);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	add_back_recast(bash, recast, minishell_name);
}

void	get_env_value(t_bash *bash, t_list **recast, char *data, int *i)
{
	int		origin;
	char	*env_var_name;
	char	*env_var_value;

	origin = *i;
	while (data[*i]
		&& ((data[*i] != '$') && (data[*i] != '\'') && (data[*i] != '\"')))
		*i += 1;
	env_var_name = ft_substr(data, origin, *i - origin);
	if (!env_var_name)
	{
		ft_lstclear(recast, &free_content);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	env_var_value = get_value(bash, env_var_name);
	free(env_var_name);
	add_back_recast(bash, recast, env_var_value);
}
