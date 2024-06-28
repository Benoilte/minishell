/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:09:32 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/27 15:30:29 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	sort_cmd_builtin(t_instruction *instruction, t_bash *bash, char **envp)
{
	t_token	*current_cmd_token;

	current_cmd_token = instruction->cmd;
	while (current_cmd_token != NULL)
	{
		if (type_equal_to(BUILTIN, current_cmd_token->data_type))
		{
			builtins(instruction, bash->env, bash);
		}
		else if (type_equal_to(CMD, current_cmd_token->data_type))
			ft_cmd(instruction, bash->env, envp);
		current_cmd_token = current_cmd_token->next;
	}
}
