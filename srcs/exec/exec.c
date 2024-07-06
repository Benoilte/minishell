/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:12 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/06 14:41:19 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int setup_pipe(t_instruction *current)
{
    if (current->next != NULL)
    {
        if (pipe(current->fd) == -1)
        {
            print_cmd_error("setup_pipe", current->cmd->data);
            return (-1);
        }
    }
    else
    {
        current->fd[0] = -1;
        current->fd[1] = -1;
    }
	return (0);
}

int handle_process(t_instruction *current, t_bash *bash, char **envp)
{
    current->pid = fork();
    if (current->pid == -1)
    {
        print_cmd_error("handle_process fork()", current->cmd->data);
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

void	exec(t_instruction *instruction, t_bash *bash, char **envp)
{
	t_env	*env;

	env = bash->env;
	if (instruction->next == NULL && (instruction->cmd->data_type & BUILTIN))
	{
		if (sort_red(STDIN_FILENO, STDOUT_FILENO, instruction, bash) < 0)
			instruction->exit_status = 1;
		else
			builtins(instruction, env, bash);
		reset_fd_std(instruction);
	}
	else if (instruction->next != NULL || (instruction->cmd->data_type & CMD))
		multi_exec(bash, instruction, envp);
	set_exit_code(bash);
}

void	set_exit_code(t_bash *bash)
{
	t_instruction	*last_inst;

	if (size_instruction(bash->instruction) == 1
		&& type_equal_to(BUILTIN, bash->instruction->cmd->data_type))
		bash->exit_code = bash->instruction->exit_status;
	else
	{
		last_inst = last_instruction(bash->instruction);
		if (last_inst->pid == -1)
			bash->exit_code = last_inst->exit_status;
		else if (WIFSIGNALED(last_inst->exit_status))
			bash->exit_code = 128 + WTERMSIG(last_inst->exit_status);
		else if (WIFEXITED(last_inst->exit_status))
			bash->exit_code = WEXITSTATUS(last_inst->exit_status);
	}
}

void	reset_fd_std(t_instruction *inst)
{
	if (inst->pid != 0)
	{
		if (dup2(inst->save_stdout, STDOUT_FILENO) < 0)
		{
			inst->exit_status = 1;
			print_cmd_error("reset_stdout dup2", inst->cmd->data);
		}
		if (close(inst->save_stdout) < 0)
		{
			inst->exit_status = 1;
			print_cmd_error("reset_stdout close", inst->cmd->data);
		}
		if (dup2(inst->save_stdin, STDIN_FILENO) < 0)
		{
			inst->exit_status = 1;
			print_cmd_error("reset_stdin dup2", inst->cmd->data);
		}
		if (close(inst->save_stdin) < 0)
		{
			inst->exit_status = 1;
			print_cmd_error("reset_stdin close", inst->cmd->data);
		}
	}
}
