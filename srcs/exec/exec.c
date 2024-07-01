/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:12 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/30 20:32:51 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/exec.h"

void setup_pipe(t_instruction *current)
{
    if (current->next != NULL)
    {
        if (pipe(current->fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
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
        if (current->prev != NULL)
            close(current->prev->fd[1]);
        child_process(current, bash, envp);
    }
    else
        parent_process(current);
}
void exec(t_instruction *instruction, t_bash *bash, char **envp)
{
    t_env *env;

    env = bash->env;
    if ((instruction->next == NULL && instruction->red != NULL) || type_equal_to(BUILTIN, instruction->cmd->data_type))
    {
        // printf("simple\n");
        builtins(instruction, env, bash);
    }
    else if (instruction->next != NULL || instruction->cmd != NULL || instruction->red != NULL)
    {
        // printf("multi\n");
        multi_exec(bash, instruction, envp);
    }
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
