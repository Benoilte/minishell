/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:15:42 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/11 15:21:50 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void cd(t_instruction *instruction)
{
    char *directory;

    if (instruction->cmd_array[1] != NULL)
        directory = instruction->cmd_array[1];
    else
    {
        directory = getenv("HOME");
        if (directory == NULL)
        {
            fprintf(stderr, "cd : HOME not set\n");
            return ;
        }
    }
    if (chdir(directory) != 0)
    {
        fprintf(stderr, "cd: %s: %s\n", directory, strerror(errno));  
        EXIT_FAILURE;
    }
}
