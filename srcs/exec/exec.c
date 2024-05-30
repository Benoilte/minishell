/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:12 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/30 13:40:19 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void exec(t_instruction *instruction, t_env *env, char **envp)
{
    t_instruction *current;
    int prev_fd[2] = {-1, -1};

    current = instruction;
    while (current != NULL)
    {
        printf("Executing command: %s\n", current->cmd_array[0]);
        if (current->next != NULL)
        {
            if (pipe(current->fd) == -1)
                perror("pipe");
        }
        else
        {
            current->fd[0] = -1;
            current->fd[1] = -1;
        }

        child_process(current, env, envp, prev_fd);

        if (prev_fd[0] != -1)
            close(prev_fd[0]);
        if (prev_fd[1] != -1)
            close(prev_fd[1]);

        prev_fd[0] = current->fd[0];
        prev_fd[1] = current->fd[1];

        current = current->next;
    }
    printf("All instructions executed.\n");
}

