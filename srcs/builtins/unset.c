/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:12:33 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/21 10:08:14 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void ft_unset(t_bash *bash)
{
    char *rl;
    char *arg;
    t_env *current;
    t_env *prev;
    
    if (ft_strncmp(bash->sequence, "unset ", 6) == 0)
    {
        rl = bash->sequence;
        arg = rl + 6;    
        current = bash->env;
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
                return ;
            }
            prev = current;
            current = current->next;
        }
    }
}
