/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_data_type.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 08:13:41 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/18 10:20:02 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	update_data_cmd_type(t_instruction *inst)
{
	if (inst->cmd == NULL)
		return (RETURN_SUCCESS);
	while (inst->cmd != NULL && (ft_strlen(inst->cmd->data) == 0)
		&& !(inst->cmd->data_type & (D_QUOTES | S_QUOTES)))
		remove_empty_expanded_first_token(inst);
	if (inst->cmd == NULL)
		return (RETURN_SUCCESS);
	if (is_builtin(inst->cmd->data) && (inst->cmd->data_type & CMD))
	{
		inst->cmd->data_type ^= (CMD | BUILTIN);
		// inst->cmd->data_type |= BUILTIN;
	}
	else if (is_builtin(inst->cmd->data) && (inst->cmd->data_type & WORD))
	{
		inst->cmd->data_type ^= (WORD | BUILTIN);
		// inst->cmd->data_type |= BUILTIN;
	}
	else if ((inst->cmd->data_type & WORD))
	{
		inst->cmd->data_type ^= (WORD | CMD);
		// inst->cmd->data_type |= CMD;
	}
	return (RETURN_SUCCESS);
}

int	remove_empty_expanded_first_token(t_instruction *instruction)
{
	t_token	*first_cmd;
	t_token	*second_cmd;

	first_cmd = instruction->cmd;
	second_cmd = instruction->cmd->next;
	instruction->cmd = second_cmd;
	first_cmd->next = NULL;
	clear_token(&first_cmd);
	return (RETURN_SUCCESS);
}
