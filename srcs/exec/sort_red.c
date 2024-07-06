/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:11 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/06 13:08:21 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/exec.h"

int	sort_red(int fd_in, int fd_out, t_instruction *instruction, t_bash *bash)
{
	t_token	*current_red_token;

	current_red_token = instruction->red;
	while (current_red_token != NULL)
	{
		if (current_red_token->data_type
			& (INPUT | OUTPUT_APPEND | OUTPUT_TRUNCATE))
		{
			if (red(fd_in, fd_out, instruction, current_red_token) < 0)
				return (-1);
		}
		else if (type_equal_to(HEREDOC, current_red_token->data_type))
			here_doc(instruction, bash);
		current_red_token = current_red_token->next;
	}
	return (0);
}

int	inst_have_input_red(t_instruction *current_inst)
{
	t_token	*red;

	red = current_inst->red;
	while (red)
	{
		if (red->data_type & (INPUT | HEREDOC))
			return (1);
		red = red->next;
	}
	return (0);
}

int	inst_have_output_red(t_instruction *current_inst)
{
	t_token	*red;

	red = current_inst->red;
	while (red)
	{
		if (red->data_type & (OUTPUT_APPEND | OUTPUT_TRUNCATE))
			return (1);
		red = red->next;
	}
	return (0);
}
