/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:54:13 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/19 11:13:04 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void echo(t_instruction *instruction)
{
    int start_index;
    int new_line;
    int i;

    new_line = 1;
    start_index = 1;
    if (instruction->cmd_array[1] != NULL
        && ft_strncmp(instruction->cmd_array[1], "-n", 2) == 0)
    {
        new_line = 0;
        start_index = 2;
    }
    i = start_index;
    while (instruction->cmd_array[i] != NULL)
    {
        if (instruction->red != NULL)
        {
            ft_putstr_fd(instruction->cmd_array[i], STDOUT_FILENO);
            if (instruction->cmd_array[i + 1] != NULL)
                ft_putstr_fd(" ", STDOUT_FILENO);
        }
        else
        {
            printf("%s", instruction->cmd_array[i]);
            if (instruction->cmd_array[i + 1] != NULL)
                printf(" ");
        }
        i++;
    }
    if (instruction->red != NULL)
    {
        if (new_line)
            ft_putstr_fd("\n", STDOUT_FILENO);
    }
    else
    {
        if (new_line)
            printf("\n");
    }
    //exit(EXIT_SUCCESS);
}
