/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:24:31 by tommartinel       #+#    #+#             */
/*   Updated: 2024/06/28 13:45:31 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void ft_exit(t_instruction *instruction, t_bash *bash)
{
    t_token *current_red;
    t_token *instruction_tmp;
    int arg_count;
    t_token *arg;
    const char *exit_message;
    int saved_stdout;

    saved_stdout = dup(STDOUT_FILENO);
    instruction_tmp = instruction->red;
    if (instruction->cmd != NULL && instruction->cmd->data != NULL && strcmp(instruction->cmd->data, "exit") == 0) 
    {
        current_red = instruction->red;
        arg_count = 0;
        arg = instruction->cmd->next;
        while (arg != NULL) 
        {
            arg_count++;
            arg = arg->next;
        }
        if (handle_exit_error(arg_count, instruction->cmd->next, instruction))
            return;
        while (current_red != NULL)
        {
            printf("Creation de fichier\n");
            instruction->red = current_red;
            sort_red(instruction, bash);
            current_red = current_red->next;
        }
        instruction->red = instruction_tmp;
        exit_message = "exit\n";
        write(saved_stdout, exit_message, strlen(exit_message));

        if (arg_count == 1)
            bash->exit_code = ft_atoi(instruction->cmd->next->data);
        clear_bash_and_exit(&bash, bash->exit_code);
        close(saved_stdout);
    }
    else
        close(saved_stdout);
}
