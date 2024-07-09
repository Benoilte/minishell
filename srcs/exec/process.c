/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:51:22 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/09 13:54:26 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	handle_process(t_instruction *current, t_bash *bash, char **envp)
{
	current->pid = fork();
	if (current->pid == -1)
	{
		print_cmd_error("handle_process fork()", current->cmd);
		return (-1);
	}
	else if (current->pid == 0)
	{
		set_sig_int(DEFAULT);
		child_process(current, bash, envp);
		clear_bash_and_exit(&bash, current->exit_status);
	}
	else
	{
		if (parent_process(current) < 0)
			current->exit_status = 1;
	}
	return (0);
}

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
	if ((inst_have_input_red(instruction->red) == 0)
		&& (instruction->prev != NULL))
	{
		if (dup2(instruction->prev->fd[0], STDIN_FILENO) < 0)
		{
			print_cmd_error("dup2_stdin", instruction->cmd);
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		}
		if (close_and_reset_fd(instruction, instruction->prev->fd) < 0)
			clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	if ((inst_have_output_red(instruction->red) == 0)
		&& (instruction->next != NULL))
	{
		if (dup2(instruction->fd[1], STDOUT_FILENO) < 0)
		{
			print_cmd_error("dup2_stdout", instruction->cmd);
			clear_bash_and_exit(&bash, EXIT_FAILURE);
		}
		if (close_and_reset_fd(instruction, instruction->fd + 1) < 0)
			clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	close_unused_fd(instruction, bash);
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
