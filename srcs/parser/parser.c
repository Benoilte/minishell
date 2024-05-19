/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:54:31 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/19 12:22:08 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing(t_bash *bash)
{
	t_instruction	*instruction;

	instruction = bash->instruction;
	while (instruction)
	{
		if (check_instruction(bash, instruction) == PARSING_ERROR)
			return (PARSING_ERROR);
		update_instruction(bash, instruction);
		instruction = instruction->next;
	}
	return (PARSING_OK);
}

int	check_instruction(t_bash *bash, t_instruction *instruction)
{
	(void)bash;
	if (!instruction->cmd && !instruction->red)
		return (print_error_msg(NULL, INSTRUCTION_EMPTY, NULL));
	return (PARSING_OK);
}

void	update_instruction(t_bash *bash, t_instruction *instruction)
{
	(void)bash;
	(void)instruction;
}
