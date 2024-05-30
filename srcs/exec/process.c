/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:51:22 by tmartin2          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/05/28 16:33:34 by tmartin2         ###   ########.fr       */
=======
/*   Updated: 2024/05/28 16:36:15 by tmartin2         ###   ########.fr       */
>>>>>>> execution
=======
/*   Updated: 2024/05/30 13:14:13 by tmartin2         ###   ########.fr       */
>>>>>>> execution
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void child_process(t_instruction *instruction, t_env *env, char **envp, int prev_fd[2])
{
    pid_t pid;

<<<<<<< HEAD
	if(pipe(instruction->fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("pipe");
	else if (pid == 0)
	{
		// Processus enfant
		if (instruction->fd[0] != -1)
		{
			close(instruction->fd[0]);
			if (instruction->next != NULL)
			{
				dup2(instruction->fd[1], STDOUT_FILENO);
			}
			close(instruction->fd[1]);
		}
		sort_array(instruction, env, envp);
		_exit(EXIT_SUCCESS);
	}
	else
	{
		// Processus parent
		if (instruction->fd[1] != -1)
		{
			close(instruction->fd[1]);
			if (instruction->next != NULL)
			{
				dup2(instruction->fd[0], STDIN_FILENO);
			}
			close(instruction->fd[0]);
		}
		waitpid(pid, &status, 0);
<<<<<<< HEAD
	}
}
=======
		
	}
}

>>>>>>> execution
=======
    pid = fork();
    if (pid == -1)
        perror("fork");
    else if (pid == 0)
    {
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
        sort_array(instruction, env, envp);
    }
    else
    {
        if (prev_fd[0] != -1)
        {
            close(prev_fd[0]);
            close(prev_fd[1]);
        }
        if (instruction->next != NULL)
            close(instruction->fd[1]);
        waitpid(pid, NULL, 0);
    }
}
>>>>>>> execution
