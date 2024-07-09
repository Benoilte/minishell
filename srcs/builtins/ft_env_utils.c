/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:32:01 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/09 22:18:12 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	add_arg_env(t_bash *bash, t_token *arg)
{
	t_token	*current_arg;

	current_arg = arg;
	while (ft_strchr(current_arg->data, '=') != NULL && current_arg)
	{
		add_back_env(&bash->env, new_env(current_arg->data));
		current_arg = current_arg->next;
	}
}

void	exec_env_cmd(t_token *cmd, t_token *arg_env,
			char **arg_cmd, t_bash *bash)
{
	set_sig_int(DEFAULT);
	add_arg_env(bash, arg_env);
	update_ms_env(bash);
	ft_cmd("env", cmd, arg_cmd, bash);
}
