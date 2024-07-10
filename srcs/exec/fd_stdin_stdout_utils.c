/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_stdin_stdout_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:58:09 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/10 21:43:58 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	reset_fd_stdout(t_instruction *inst);
static void	reset_fd_stdin(t_instruction *inst);

void	reset_fd_stdin_and_stdout(t_instruction *inst)
{
	if (inst->save_stdin != -1)
		reset_fd_stdin(inst);
	if (inst->save_stdout != -1)
		reset_fd_stdout(inst);
}

void	reset_fd_stdin(t_instruction *inst)
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
	inst->save_stdin = -1;
}

void	reset_fd_stdout(t_instruction *inst)
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
	inst->save_stdout = -1;
}

int	save_fd_stdin(t_instruction *inst, t_token *current_red)
{
	if (inst_have_input_red(current_red))
	{
		inst->save_stdin = dup(STDIN_FILENO);
		if (inst->save_stdin == -1)
		{
			print_red_error("save_fd_stdin()", current_red);
			return (-1);
		}
	}
	return (0);
}

int	save_fd_stdout(t_instruction *inst, t_token *current_red)
{
	if (inst_have_output_red(current_red))
	{
		inst->save_stdout = dup(STDOUT_FILENO);
		if (inst->save_stdout == -1)
		{
			print_red_error("save_fd_stdout()", current_red);
			return (-1);
		}
	}
	return (0);
}
