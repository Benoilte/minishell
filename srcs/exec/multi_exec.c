/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:02:02 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/08 12:59:45 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	multi_exec(t_bash *bash, t_instruction *instruction, char **envp)
{
	t_instruction	*current;

	instruction->prev = NULL;
	current = instruction;
	while (current != NULL)
	{
		setup_pipe(current);
		if (sort_red(STDIN_FILENO, STDOUT_FILENO, current, bash) < 0)
			current->exit_status = 1;
		else
			handle_process(current, bash, envp);
		reset_fd_stdin(current);
		reset_fd_stdout(current);
		current = current->next;
	}
	current = instruction;
	while (current != NULL)
	{
		waitpid(current->pid, &current->exit_status, 0);
		current = current->next;
	}
}
