/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:12 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/05 09:19:15 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/exec.h"

void setup_pipe(t_instruction *current)
{
    if (current->next != NULL)
    {
        if (pipe(current->fd) < 0)
		{
			print_cmd_error("setup_pie", current->cmd->data);
			current->exit_status = 1;
		}
    }
    else
    {
        current->fd[0] = -1;
        current->fd[1] = -1;
    }
}

void handle_process(t_instruction *current, t_bash *bash, char **envp)
{
    current->pid = fork();
    if (current->pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (current->pid == 0)
    {
		set_sig_int(DEFAULT);
        // if (current->prev != NULL)
        //     close(current->prev->fd[1]);
        child_process(current, bash, envp);
		clear_bash_and_exit(&bash, current->exit_status);
    }
    else
        parent_process(current);
}

void	exec(t_instruction *instruction, t_bash *bash, char **envp)
{
	t_env	*env;

	env = bash->env;
	if (instruction->next == NULL && (instruction->cmd->data_type & BUILTIN))
	{
		if (sort_red(instruction, bash) < 0)
			instruction->exit_status = 1;
		else
			builtins(instruction, env, bash);
	}
	else if (instruction->next != NULL || instruction->cmd->data_type == 512)
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
		if (WIFSIGNALED(last_inst->exit_status))
			bash->exit_code = 128 + WTERMSIG(last_inst->exit_status);
		if (WIFEXITED(last_inst->exit_status))
			bash->exit_code = WEXITSTATUS(last_inst->exit_status);
	}
}
