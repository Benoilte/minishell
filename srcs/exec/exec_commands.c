/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:02:02 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/15 23:56:54 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_commands(t_bash *bash, t_instruction *instr)
{
	t_instruction	*current;
	t_instruction	*last_inst;

	current = instr;
	last_inst = last_instruction(instr);
	while (current != NULL)
	{
		if (setup_pipe(current) < 0)
			break ;
		if (sort_red(current, bash) < 0)
		{
			if (current->exit_status == 130)
			{
				last_inst->exit_status = 130;
				break ;
			}
			else
				current->exit_status = 1;
		}
		else
			handle_process(current, bash);
		reset_fd_stdin_and_stdout(current);
		current = current->next;
	}
	wait_child_process(instr);
}
