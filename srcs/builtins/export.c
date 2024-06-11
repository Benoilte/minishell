/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:04:33 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/11 16:09:20 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int set_env_var_liste(t_env *env, char *envp)
{
    t_env *new;
    t_env *current;

    new = new_env(envp);
    if(!new)
        return (0);
    current = env;
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
    add_back_env(&env, new);
    return (1);
}
void ft_export(t_env *env, t_instruction *instruction)
{
    t_env *current;
    int start_index;

    current = env;
    start_index = 1;
    if (instruction->cmd_array[1] == NULL)
    {
        while (current)
        {
   		if (instruction->red != NULL)
		{   
            ft_putstr_fd("declare -x ", STDOUT_FILENO);
            ft_putstr_fd(current->name, STDOUT_FILENO);
            ft_putstr_fd("=", STDOUT_FILENO);
            ft_putendl_fd(current->value, STDOUT_FILENO);
		}
        else
            printf("declare -x %s=%s\n", current->name, current->value);
        current = current->next; 
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        start_index = 1;
        while (instruction->cmd_array[start_index] != NULL)
        {
            if (instruction->red != NULL)
                exit(EXIT_SUCCESS);
            else if (ft_strchr(instruction->cmd_array[start_index], '=') != NULL)
            {
                if (!set_env_var_liste(env, instruction->cmd_array[start_index]))
                    fprintf(stderr, "export: error setting environment variable\n");
            }
            else
                fprintf(stderr, "export: invalid input: %s\n", instruction->cmd_array[start_index]);
            start_index++;
        }
    }
}
