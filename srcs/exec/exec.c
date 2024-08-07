/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:12 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/15 23:53:54 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec(t_instruction *inst, t_bash *bash)
{
	if (inst->next == NULL && inst->cmd == NULL)
	{
		if (sort_red(inst, bash) < 0 && inst->exit_status != 130)
			inst->exit_status = 1;
		reset_fd_stdin_and_stdout(inst);
	}
	else if (inst->next == NULL && (inst->cmd->data_type & BUILTIN))
	{
		if (sort_red(inst, bash) < 0)
		{
			if (inst->exit_status != 130)
				inst->exit_status = 1;
		}
		else
			builtins(inst, bash);
		reset_fd_stdin_and_stdout(inst);
	}
	else
		exec_commands(bash, inst);
	set_exit_code(bash);
}

void	set_exit_code(t_bash *bash)
{
	t_instruction	*last_inst;

	last_inst = last_instruction(bash->instruction);
	if (last_inst->cmd == NULL)
		bash->exit_code = bash->instruction->exit_status;
	else if (size_instruction(bash->instruction) == 1
		&& type_equal_to(BUILTIN, bash->instruction->cmd->data_type))
		bash->exit_code = bash->instruction->exit_status;
	else
	{
		if (last_inst->pid == -1)
			bash->exit_code = last_inst->exit_status;
		else if (WIFSIGNALED(last_inst->exit_status))
			bash->exit_code = 128 + WTERMSIG(last_inst->exit_status);
		else if (WIFEXITED(last_inst->exit_status))
			bash->exit_code = WEXITSTATUS(last_inst->exit_status);
	}
}
