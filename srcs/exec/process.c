/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:51:22 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/28 13:21:33 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void parent_process(t_instruction *instruction)
{
    if (instruction->prev != NULL)
        close(instruction->prev->fd[0]);
    if (instruction->next != NULL)
        close(instruction->fd[1]);  
}
void child_process(t_instruction *instruction, t_bash *bash, char **envp)
{
    if (instruction->prev != NULL)
    {
        dup2(instruction->prev->fd[0], STDIN_FILENO);
        close(instruction->prev->fd[0]);
    }
    if (instruction->next != NULL)
    {
        dup2(instruction->fd[1], STDOUT_FILENO);
        close(instruction->fd[1]);
    }
    if (instruction->fd[0] != -1)
        close(instruction->fd[0]);
    if (instruction->fd[1] != -1)
        close(instruction->fd[1]);
    while (instruction->red != NULL && ft_strcmp(instruction->cmd->data, "exit") != 0)
    {
        sort_red(instruction, bash);
        instruction->red = instruction->red->next;
    }
    if (instruction->cmd != NULL || instruction->prev != NULL || ft_strcmp(instruction->cmd->data, "exit") == 0)
        sort_cmd_builtin(instruction, bash, envp);
}
