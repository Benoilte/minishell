/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:51:22 by tmartin2          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/20 18:01:13 by tom              ###   ########.fr       */
=======
/*   Updated: 2024/06/19 11:10:39 by tommartinel      ###   ########.fr       */
>>>>>>> refs/remotes/origin/master
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void parent_process(t_instruction *instruction)
{
    if (instruction->prev != NULL)
    {
        close(instruction->prev->fd[0]);
    }
    if (instruction->next != NULL)
        close(instruction->fd[1]);  
}
void child_process(t_instruction *instruction, t_bash *bash, char **envp)
{
    if (instruction->prev != NULL)
    {
<<<<<<< HEAD
        //printf("Redirection de stdin vers fd : %d\n", instruction->prev->fd[0]);
        dup2(instruction->prev->fd[0], STDIN_FILENO);
=======
        if (dup2(instruction->prev->fd[0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
>>>>>>> refs/remotes/origin/master
        close(instruction->prev->fd[0]);
    }
    if (instruction->next != NULL)
    {
<<<<<<< HEAD
        //printf("Redirection de stdout vers fd : %d\n", instruction->fd[1]);
        dup2(instruction->fd[1], STDOUT_FILENO);
        close(instruction->fd[1]);
=======
        if (dup2(instruction->fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
       close(instruction->fd[1]);
>>>>>>> refs/remotes/origin/master
    }
        // Fermer les descripteurs de fichiers inutilisés
    if (instruction->fd[0] != -1)
        close(instruction->fd[0]);
    if (instruction->fd[1] != -1)
        close(instruction->fd[1]);
    while (instruction->red != NULL)
    {
        sort_red(instruction);
       instruction->red =instruction->red->next;
    }
    if (instruction->cmd != NULL || instruction->prev != NULL)
        sort_cmd_builtin(instruction, bash, envp);
    exit(EXIT_SUCCESS);
}
