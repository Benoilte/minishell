/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:12 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/28 15:23:46 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"


void	exec(t_instruction *instruction, t_env *env, char **envp)
{
	t_instruction *current;

	current = instruction;
	while (current != NULL)
	{
		printf("Executing command: %s\n", instruction->cmd_array[0]);
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
		int i = 0;
			child_process(instruction, env, envp);
			i++;
		current = current->next;
	}
	printf("All instructions executed.\n");
}
