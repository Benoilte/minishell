/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:54:31 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/18 08:13:54 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	parsing(t_bash *bash)
{
	t_instruction	*instruction;
	int				nb_next_inst;

	instruction = bash->instruction;
	nb_next_inst = size_instruction(instruction);
	while (instruction)
	{
		if (check_instruction(instruction, nb_next_inst - 1) == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
		if (update_instruction(bash, instruction) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		if (fill_cmd_array(instruction, instruction->cmd) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		instruction = instruction->next;
		nb_next_inst--;
	}
	return (SYNTAX_OK);
}

int	sequence_is_filled(t_instruction *instruction)
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

int	check_instruction(t_instruction *instruction, int nb_next_inst)
{
	t_token	*red;
	t_token	*cmd;

	red = instruction->red;
	cmd = instruction->cmd;
	if (!cmd && !red)
	{
		print_parsing_error_msg(UNEXPECTED_TOKEN, "|", 0);
		return (SYNTAX_ERROR);
	}
	while (red)
	{
		if (check_redirections(red, nb_next_inst) == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
		red = red->next;
	}
	while (cmd)
	{
		if (check_cmd(cmd) == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
		cmd = cmd->next;
	}
	return (SYNTAX_OK);
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
	if (update_data_cmd_type(instruction) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
