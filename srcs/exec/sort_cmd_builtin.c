/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:09:32 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/31 17:25:26 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void sort_cmd_builtin(t_instruction *instruction, t_env *env, char **envp)
{
    t_token	*current_cmd_token;

    current_cmd_token = instruction->cmd;
	while (current_cmd_token != NULL)
    {
        if (current_cmd_token->data_type == BUILTIN)
        {
            builtins(instruction, env);
        }
        else if (current_cmd_token->data_type == CMD)
        {
            ft_cmd(instruction, env, envp);
			 // Retourner après avoir exécuté une commande externe
        }
        current_cmd_token = current_cmd_token->next;
    }
}