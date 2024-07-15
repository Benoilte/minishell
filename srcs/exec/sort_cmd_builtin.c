/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:09:32 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/15 23:48:28 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	sort_cmd_builtin(t_instruction *instruction, t_bash *bash, char **envp)
{
	t_token	*current_cmd_token;

	(void)envp;
	current_cmd_token = instruction->cmd;
	while (current_cmd_token != NULL)
	{
		if (type_equal_to(BUILTIN, current_cmd_token->data_type))
		{
			builtins(instruction, bash);
		}
		else if (type_equal_to(CMD, current_cmd_token->data_type))
			ft_cmd("minishell", instruction->cmd, instruction->cmd_array, bash);
		current_cmd_token = current_cmd_token->next;
	}
}
