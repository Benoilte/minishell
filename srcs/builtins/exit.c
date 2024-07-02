/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:24:31 by tommartinel       #+#    #+#             */
/*   Updated: 2024/07/02 13:36:26 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void ft_exit(t_instruction *instruction, t_bash *bash)
{
    t_token *instruction_tmp;
    int arg_count;
    t_token *arg;

    instruction_tmp = instruction->red;
    if (instruction->cmd != NULL && instruction->cmd->data != NULL && strcmp(instruction->cmd->data, "exit") == 0) 
    {
        arg_count = 0;
        arg = instruction->cmd->next;
        while (arg != NULL) 
        {
            arg_count++;
            arg = arg->next;
        }
        if (handle_exit_error(arg_count, instruction->cmd->next, instruction))
            return;
        instruction->red = instruction_tmp;
        if (instruction->save_stdout != -1)
	    {
		    dup2(instruction->save_stdout, STDOUT_FILENO);
		    close(instruction->save_stdout);
		    instruction->save_stdout = -1;
	    }
        if (arg_count == 1)
            bash->exit_code = ft_atoi(instruction->cmd->next->data);
        printf("exit\n");
        clear_bash_and_exit(&bash, bash->exit_code);
    }
}
