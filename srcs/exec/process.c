/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:51:22 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/18 14:22:11 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void child_process(t_instruction *instruction, t_bash *bash, char **envp)
{
    if (instruction->prev != NULL)
    {
        //printf("Redirection de stdin vers fd : %d\n", instruction->prev->fd[0]);
        if (dup2(instruction->prev->fd[0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(instruction->prev->fd[0]);
    }
    if (instruction->next != NULL)
    {
        //printf("Redirection de stdout vers fd : %d\n", instruction->fd[1]);
        if (dup2(instruction->fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
       close(instruction->fd[1]);
    }
    while (instruction->red != NULL)
    {
        sort_red(instruction);
       instruction->red =instruction->red->next;
    }
    if (instruction->cmd != NULL)
        sort_cmd_builtin(instruction, bash, envp);
    exit(EXIT_SUCCESS);
}
