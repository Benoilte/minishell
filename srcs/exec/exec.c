/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:12 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/20 16:07:03 by tom              ###   ########.fr       */
/*   Updated: 2024/06/18 15:21:06 by tommartinel      ###   ########.fr       */
/*   Updated: 2024/06/18 19:32:35 by bebrandt         ###   ########.fr       */
                                                               */
/* ************************************************************************** */

#include "../../includes/exec.h"

void ft_exit(t_instruction *instruction, t_bash *bash)
{
    t_token *current_red;

    if (instruction->cmd != NULL && instruction->cmd->data != NULL && strcmp(instruction->cmd->data, "exit") == 0)
    {
        current_red = instruction->red;
        while (current_red != NULL)
        {
            instruction->red = current_red;
            red(instruction);
            current_red = current_red->next;
        }
        printf("exit\n");
        clear_bash_and_exit(&bash, 0);
    }
}
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
    t_instruction *current;
    int status;

    env = bash->env;
    instruction->prev = NULL;
    current = instruction;
    ft_exit(instruction, bash);
    while (current != NULL)
    {
        setup_pipe(current);
        handle_process(current, bash, envp);
        if (instruction->next == NULL && instruction->red == NULL && type_equal_to(BUILTIN, instruction->cmd->data_type))
            builtins(instruction, env);
        if (current->next != NULL)
            current->next->prev = current;
        current = current->next;
    }
    current = instruction;
    while (current != NULL)
    {
        waitpid(current->pid, &status, 0);
        current = current->next;
    }
}
