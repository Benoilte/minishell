/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:54:31 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/10 17:13:46 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	parsing(t_bash *bash)
{
	t_instruction	*instruction;

	instruction = bash->instruction;
	if (sequence_is_empty(instruction) == SEQUENCE_EMPTY)
		return (SEQUENCE_EMPTY);
	while (instruction)
	{
		if (check_instruction(instruction) == PARSING_ERROR)
			return (PARSING_ERROR);
		if (update_instruction(bash, instruction) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		if (fill_cmd_array(instruction) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		instruction = instruction->next;
	}
	return (PARSING_OK);
}

int	sequence_is_empty(t_instruction *instruction)
{
	t_token			*red;
	t_token			*cmd;
	t_instruction	*next;

	red = instruction->red;
	cmd = instruction->cmd;
	next = instruction->next;
	if ((size_instruction(instruction) == 1) && !cmd && !red && !next)
		return (SEQUENCE_EMPTY);
	else
		return (SEQUENCE_IS_FILLED);
}

int	check_instruction(t_instruction *instruction)
{
	t_token	*red;
	t_token	*cmd;

	red = instruction->red;
	cmd = instruction->cmd;
	if (!cmd && !red)
		return (print_parsing_error_msg(INSTRUCTION_EMPTY, NULL, 0));
	while (red)
	{
		if (check_redirections(red) == PARSING_ERROR)
			return (PARSING_ERROR);
		red = red->next;
	}
	while (cmd)
	{
		if (check_cmd(cmd) == PARSING_ERROR)
			return (PARSING_ERROR);
		cmd = cmd->next;
	}
	return (PARSING_OK);
}

int	update_instruction(t_bash *bash, t_instruction *instruction)
{
	t_token	*red;
	t_token	*cmd;

	red = instruction->red;
	cmd = instruction->cmd;
	while (red)
	{
		red->option = update_data(bash, red->option);
		if (!red->option)
			return (RETURN_FAILURE);
		red = red->next;
	}
	while (cmd)
	{
		cmd->data = update_data(bash, cmd->data);
		if (!cmd->data)
			return (RETURN_FAILURE);
		cmd = cmd->next;
	}
	return (RETURN_SUCCESS);
}
