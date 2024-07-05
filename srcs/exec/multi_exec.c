/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:02:02 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/05 07:40:42 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void multi_exec(t_bash *bash, t_instruction *instruction, char **envp)
{
    t_instruction *current;

    current = instruction;
    while (current != NULL)
    {
        setup_pipe(current);
        current = current->next;
    }
    current = instruction;
    while (current != NULL)
    {
        // setup_pipe(current);
        handle_process(current, bash, envp);
        current = current->next;
    }
    current = instruction;
    while (current != NULL)
    {
        waitpid(current->pid, &current->exit_status, 0);
        current = current->next;
    }
}
