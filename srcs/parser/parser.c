/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:54:31 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/19 13:06:05 by bebrandt         ###   ########.fr       */
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
	t_token	*red;
	t_token	*cmd;

	(void)bash;
	red = instruction->red;
	cmd = instruction->cmd;
	if (!cmd && !red)
		return (print_parsing_error_msg(INSTRUCTION_EMPTY, NULL));
	while (red)
	{
		if (check_redirections(red) == PARSING_ERROR)
			return (PARSING_ERROR);
		red = red->next;
	}
	return (PARSING_OK);
}

void	update_instruction(t_bash *bash, t_instruction *instruction)
{
	(void)bash;
	(void)instruction;
}
