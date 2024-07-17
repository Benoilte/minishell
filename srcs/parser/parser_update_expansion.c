/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_expansion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:13:10 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/17 10:59:07 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	get_dollar_sign(t_list **recast)
{
	char	*dollar;

	dollar = ft_strdup("$");
	if (!dollar)
		return (RETURN_FAILURE);
	return (add_back_recast(recast, dollar));
}

int	get_last_cmd_exit_status(t_list **recast, int *i, int exit_status)
{
	char	*last_cmd_exit_status;

	*i += 1;
	last_cmd_exit_status = ft_itoa(exit_status);
	if (!last_cmd_exit_status)
		return (RETURN_FAILURE);
	return (add_back_recast(recast, last_cmd_exit_status));
}

int	get_process_id(t_list **recast, int *i)
{
	char	*process_id;

	*i += 1;
	process_id = ft_strdup("0");
	if (!process_id)
		return (RETURN_FAILURE);
	return (add_back_recast(recast, process_id));
}

int	get_minishell_name(t_list **recast, int *i)
{
	char	*minishell_name;

	*i += 1;
	minishell_name = ft_strdup("minishell");
	if (!minishell_name)
		return (RETURN_FAILURE);
	return (add_back_recast(recast, minishell_name));
}

int	get_env_value(t_list **recast, t_env *env, char *data, int *i)
{
	int		origin;
	char	*env_var_name;
	char	*env_var_value;

	origin = *i;
	while (data[*i]
		&& ((data[*i] != '$')
			&& (data[*i] != '\'')
			&& (data[*i] != '\"')
			&& (data[*i] != '/')
			&& (data[*i] != ' ')))
		*i += 1;
	env_var_name = ft_substr(data, origin, *i - origin);
	if (!env_var_name)
	{
		ft_lstclear(recast, &free_content);
		return (RETURN_FAILURE);
	}
	env_var_value = get_value(env, env_var_name);
	free(env_var_name);
	if (!env_var_value)
		return (RETURN_FAILURE);
	return (add_back_recast(recast, env_var_value));
}
