/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:51:22 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/30 13:41:42 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void child_process(t_instruction *instruction, t_env *env, char **envp, int prev_fd[2])
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        // Processus enfant
        if (prev_fd[0] != -1)
        {
            close(prev_fd[1]);
            dup2(prev_fd[0], STDIN_FILENO);
            close(prev_fd[0]);
        }

        if (instruction->next != NULL)
        {
            close(instruction->fd[0]);
            dup2(instruction->fd[1], STDOUT_FILENO);
            close(instruction->fd[1]);
        }

        ft_cmd(instruction, env, envp);
    }
    else
    {
        // Processus parent
        if (prev_fd[0] != -1)
        {
            close(prev_fd[0]);
            close(prev_fd[1]);
        }

        if (instruction->next != NULL)
        {
            close(instruction->fd[1]);
        }

        waitpid(pid, NULL, 0);
    }
}
