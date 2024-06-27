/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:02:02 by tommartinel       #+#    #+#             */
/*   Updated: 2024/06/25 17:53:20 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void multi_exec(t_bash *bash, t_instruction *instruction, char **envp)
{
    t_instruction *current;

    instruction->prev = NULL;
    current = instruction;
    while (current != NULL)
    {
        setup_pipe(current);
        handle_process(current, bash, envp);
        if (current->next != NULL)
            current->next->prev = current;
        current = current->next;
    }
    current = instruction;
    while (current != NULL)
    {
        waitpid(current->pid, &current->exit_status, 0);
        current = current->next;
    }
}