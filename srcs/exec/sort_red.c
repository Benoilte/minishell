/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:11 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/12 14:26:06 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	sort_red(t_instruction *instruction, t_bash *bash)
{
	t_token	*current_red;

	current_red = instruction->red;
	if (save_fd_stdin(instruction, current_red) < 0)
		return (-1);
	if (save_fd_stdout(instruction, current_red) < 0)
		return (-1);
	while (current_red != NULL)
	{
		if (current_red->data_type & (INPUT | OUTPUT_APPEND | OUTPUT_TRUNCATE))
		{
			if (red(current_red) < 0)
				return (-1);
		}
		else if (current_red->data_type & (HEREDOC))
		{
			if (setup_here_doc(instruction, current_red, bash) < 0)
				return (-1);
		}
		current_red = current_red->next;
	}
	return (0);
}

int	setup_pipe(t_instruction *current)
{
	t_instruction	*last_inst;

	last_inst = last_instruction(current);
	if (current->next != NULL)
	{
		if (pipe(current->fd) == -1)
		{
			current = last_inst;
			current->exit_status = EXIT_FAILURE;
			last_inst->exit_status = EXIT_FAILURE;
			print_cmd_error("setup_pipe", current->cmd);
			return (-1);
		}
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
