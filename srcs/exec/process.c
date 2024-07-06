/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:51:22 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/06 16:30:19 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	parent_process(t_instruction *instruction)
{
	if (instruction->prev != NULL)
	{
		if (close_and_reset_fd(instruction, instruction->prev->fd) < 0)
			return (-1);
	}
	if (instruction->next != NULL)
	{
		if (close_and_reset_fd(instruction, instruction->fd + 1) < 0)
			return (-1);
	}
	return (0);
}

void	child_process(t_instruction *instruction, t_bash *bash, char **envp)
{
	if ((inst_have_input_red(instruction) == 0) && (instruction->prev != NULL))
	{
		if (dup2(instruction->prev->fd[0], STDIN_FILENO) < 0)
		{
			print_cmd_error("dup2_stdin", instruction->cmd->data);
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		}
		if (close_and_reset_fd(instruction, instruction->prev->fd) < 0)
			clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	if ((inst_have_output_red(instruction) == 0) && (instruction->next != NULL))
	{
		if (dup2(instruction->fd[1], STDOUT_FILENO) < 0)
		{
			print_cmd_error("dup2_stdout", instruction->cmd->data);
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		}
		if (close_and_reset_fd(instruction, instruction->fd + 1) < 0)
			clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	close_unused_fd(instruction, bash);
	if (instruction->cmd != NULL || instruction->prev != NULL || ft_strcmp(instruction->cmd->data, "exit") == 0)
		sort_cmd_builtin(instruction, bash, envp);
}

int	wait_child_process(t_instruction *instruction)
{
	t_instruction	*current_inst;

	current_inst = instruction;
	while (current_inst != NULL)
	{
		if (waitpid(current_inst->pid, &current_inst->exit_status, 0) == -1)
			return (-1);
		current_inst = current_inst->next;
	}
	return (0);
}

int	close_and_reset_fd(t_instruction *curent_inst, int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) < 0)
		{
			print_cmd_error("close", curent_inst->cmd->data);
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
