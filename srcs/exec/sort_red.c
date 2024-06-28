/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:11 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/27 15:18:23 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	sort_red(t_instruction *instruction, t_bash *bash)
{
	t_token	*current_red_token;
	current_red_token = instruction->red;
	while (current_red_token != NULL)
	{
		if (type_equal_to(OUTPUT_TRUNCATE, current_red_token->data_type)
			|| type_equal_to(OUTPUT_APPEND, current_red_token->data_type)
			|| type_equal_to(INPUT, current_red_token->data_type))
			red(instruction);
		else if (type_equal_to(HEREDOC, current_red_token->data_type))
			here_doc(instruction, bash);
		current_red_token = current_red_token->next;
	}
}
