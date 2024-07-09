/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_desriptors_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 07:45:32 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/09 08:27:37 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	reset_fd_stdin_and_stdout(t_instruction *inst)
{
	reset_fd_stdin(inst);
	reset_fd_stdout(inst);
}

void	reset_fd_stdin(t_instruction *inst)
{
	if (inst->pid != 0)
	{
		if (dup2(inst->save_stdin, STDIN_FILENO) < 0)
		{
			inst->exit_status = 1;
			print_cmd_error("reset_stdin dup2", inst->cmd);
		}
		if (close(inst->save_stdin) < 0)
		{
			inst->exit_status = 1;
			print_cmd_error("reset_stdin close", inst->cmd);
		}
	}
}

void	reset_fd_stdout(t_instruction *inst)
{
	if (inst->pid != 0)
	{
		if (dup2(inst->save_stdout, STDOUT_FILENO) < 0)
		{
			inst->exit_status = 1;
			print_cmd_error("reset_stdout dup2", inst->cmd);
		}
		if (close(inst->save_stdout) < 0)
		{
			inst->exit_status = 1;
			print_cmd_error("reset_stdout close", inst->cmd);
		}
	}
}

int	close_and_reset_fd(t_instruction *curent_inst, int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) < 0)
		{
			print_cmd_error("close", curent_inst->cmd);
			return (-1);
		}
		*fd = -1;
	}
	return (0);
}

void	close_unused_fd(t_instruction *current_inst, t_bash *bash)
{
	if (current_inst->fd[0] != -1)
	{
		if (close_and_reset_fd(current_inst, current_inst->fd) < 0)
			clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	if (current_inst->fd[1] != -1)
	{
		if (close_and_reset_fd(current_inst, current_inst->fd + 1) < 0)
			clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
}
