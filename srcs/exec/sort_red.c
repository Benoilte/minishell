/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:11 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/02 19:56:15 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
			if (red(instruction, current_red_token) < 0)
				return (-1);
		}
		else if (type_equal_to(HEREDOC, current_red_token->data_type))
			here_doc(instruction, bash);
		current_red_token = current_red_token->next;
	}
	return (0);
}

// int	sort_red(t_instruction *instruction, t_bash *bash)
// {
// 	t_token	*current_red_token;

// 	ft_putendl_fd(instruction->cmd->data, STDERR_FILENO);
// 	current_red_token = instruction->red;
// 	while (current_red_token != NULL)
// 	{
// 		ft_putstr_fd(current_red_token->data, STDERR_FILENO);
// 		ft_putendl_fd(current_red_token->option, STDERR_FILENO);
// 		if (type_equal_to(OUTPUT_TRUNCATE, current_red_token->data_type)
// 			|| type_equal_to(OUTPUT_APPEND, current_red_token->data_type)
// 			|| type_equal_to(INPUT, current_red_token->data_type))
// 		{
// 			if (red(instruction, current_red_token) < 0)
// 				return (-1);
// 		}
// 		else if (type_equal_to(HEREDOC, current_red_token->data_type))
// 			here_doc(instruction, bash);
// 		current_red_token = current_red_token->next;
// 	}
// }
