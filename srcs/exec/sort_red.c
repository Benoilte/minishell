/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:11 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/08 17:40:45 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	sort_red(t_instruction *instruction, t_bash *bash)
{
	t_token	*current_red_token;

	current_red_token = instruction->red;
	while (current_red_token != NULL)
	{
		if (current_red_token->data_type
			& (INPUT | OUTPUT_APPEND | OUTPUT_TRUNCATE))
		{
			if (red(current_red_token) < 0)
				return (-1);
		}
		else if (current_red_token->data_type & (HEREDOC))
		{
			if (here_doc(instruction, bash, current_red_token) < 0)
				return (-1);
		}
		current_red_token = current_red_token->next;
	}
	return (0);
}

int	inst_have_input_red(t_token *current_red)
{
	t_token	*tmp_red;

	tmp_red = current_red;
	while (tmp_red)
	{
		if (tmp_red->data_type & (INPUT | HEREDOC))
			return (1);
		tmp_red = tmp_red->next;
	}
	return (0);
}

int	inst_have_output_red(t_token *current_red)
{
	t_token	*output_red;

	output_red = current_red;
	while (output_red)
	{
		if (output_red->data_type & (OUTPUT_APPEND | OUTPUT_TRUNCATE))
			return (1);
		output_red = output_red->next;
	}
	return (0);
}
