/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:12:33 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/27 13:16:01 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void ft_unset(t_env **env, t_instruction *instruction)
{
    char *arg;
    t_env *current;
    t_env *prev;
    int i;

    i = 1;
    while (instruction->cmd_array[i] != NULL)
    {
        arg = instruction->cmd_array[i];    
        current = *env;
        prev = NULL;
        while (current)
        {
            if (ft_strcmp(current->name, arg) == 0)
            {
                if (prev == NULL)
                    current = current->next;
                if (prev != NULL)
                    prev->next = current->next;
                free(current->name);
                free(current->value);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
}
