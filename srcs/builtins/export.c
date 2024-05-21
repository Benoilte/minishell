/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:04:33 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/20 16:09:59 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int set_env_var_liste(t_bash *bash, char *envp)
{
    t_env *new;
    t_env *current;

    new = new_env(envp);
    if(!new)
        return (0);
    current = bash->env;
    while (current)
    {
        if (ft_strcmp(current->name, new->name) == 0)
        {
            free(current->value);
            current->value = new->value;
            free(new->name);
            free(new);
            return (1);
        }
        current = current->next;
    }
    add_back_env(&bash->env, new);
    return (1);
}
void ft_export(t_env *env, t_bash *bash)
{
    t_env *current;
    char *rl;
    char *msg;

    current = env;
    if (ft_strcmp(bash->sequence, "export") == 0)
    {
        while (current)
        {
            printf("declare -x %s=%s\n", current->name, current->value);
            current = current->next; 
        }
    }
    if (ft_strncmp(bash->sequence, "export ", 7) == 0)
    {
        rl = bash->sequence;
        msg = rl + 7;
            if(current->name && current->value)
                set_env_var_liste(bash, msg);
            else
                printf("export : invalid input\n");
    }
}
