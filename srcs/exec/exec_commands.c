/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:02:02 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/17 07:30:45 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	handle_error_red_in_multiple_cmd(t_instruction *current);

void	exec_commands(t_bash *bash, t_instruction *instr, char **envp)
{
	t_instruction	*current;

	current = instr;
	while (current != NULL)
	{
		if (setup_pipe(current) < 0)
			break ;
		if (sort_red(current, bash) < 0)
		{
			if (handle_error_red_in_multiple_cmd(current) == 130)
				break ;
		}
		else
			handle_process(current, bash);
		reset_fd_stdin_and_stdout(current);
		current = current->next;
	}
	wait_child_process(instr);
}

static int	handle_error_red_in_multiple_cmd(t_instruction *current)
{
	t_instruction	*last_inst;

	last_inst = last_instruction(current);
	if (current->prev != NULL)
		close_and_reset_pipe_fd(current, current->prev->fd);
	close_and_reset_pipe_fd(current, current->fd + 1);
	if (current->exit_status == 130)
	{
		last_inst->exit_status = 130;
		return (last_inst->exit_status);
	}
	else
		current->exit_status = 1;
	return (0);
}
