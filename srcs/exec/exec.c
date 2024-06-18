/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:12 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/18 14:42:57 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/exec.h"

int	ft_strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0') || (*s2 != '\0'))
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}
void exec(t_instruction *instruction, t_bash *bash, char **envp)
{
    t_instruction *current;
    pid_t pid;
    int status;

    // Initialisation de prev pour la première instruction
    instruction->prev = NULL;
    current = instruction;
    if (ft_strcmp(current->cmd->data, "exit") == 0 && current->next == NULL)
    {
        printf("exit\n");
        clear_bash_and_exit(&bash, 0);

    }
    while (current != NULL)
    {
        if (current->next != NULL)
        {
            if (pipe(current->fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            //printf("Pipe créé: fd[0] = %d, fd[1] = %d\n", current->fd[0], current->fd[1]);
        }
        else
        {
            current->fd[0] = -1;
            current->fd[1] = -1;
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
			set_signal_action(CHILD);
            // Processus enfant
            if (current->prev != NULL)
                close(current->prev->fd[1]);  // L'enfant ne lit pas du côté écriture du pipe précédent
            child_process(current, bash, envp);
        }
        else
        {
            // Processus parent
            if (current->prev != NULL)
                //printf("Parent ferme prev->fd[0]: %d\n", current->prev->fd[0]);
                close(current->prev->fd[0]);  // Le parent n'a plus besoin du côté lecture du pipe précédent
            if (current->next != NULL)
                //printf("Parent ferme current->fd[1]: %d\n", current->fd[1]);
                close(current->fd[1]);  // Le parent n'a plus besoin du côté écriture du pipe actuel
        }
        // Mise à jour du pointeur prev pour la prochaine instruction
        if (current->next != NULL)
            current->next->prev = current;
        current = current->next;
    }
    // Attendre la fin de tous les processus enfants
    current = instruction;
    while (current != NULL)
    {
        waitpid(pid, &status, 0);
        current = current->next;
    }
}

