/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:02:02 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/11 12:41:34 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_commands(t_bash *bash, t_instruction *instr, char **envp)
{
	t_instruction	*current;
	t_instruction	*last_inst;

	current = instr;
	last_inst = last_instruction(instr);
	while (current != NULL)
	{
		setup_pipe(current);
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
			handle_process(current, bash, envp);
		reset_fd_stdin_and_stdout(current);
		current = current->next;
	}
	wait_child_process(instr);
}
