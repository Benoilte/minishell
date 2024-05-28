/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:11 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/28 15:30:21 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	sort_array(t_instruction *instruction, t_env *env, char **envp)
{
	int		i;
	t_token	*current_cmd_token;
	t_token	*current_red_token;

	i = 0;
	current_cmd_token = instruction->cmd;
	current_red_token = instruction->red;
	// Afficher les infomation de cmd
    while (current_cmd_token != NULL)
    {
        if (current_cmd_token->data_type == BUILTIN)
        {
            printf("Executing builtin command\n");
            builtins(instruction, env);
            return;  // Retourner après avoir exécuté une commande builtin
        }
        else if (current_cmd_token->data_type == CMD)
        {
            printf("Executing external command\n");
            ft_cmd(instruction, env, envp);
            return;  // Retourner après avoir exécuté une commande externe
        }
        current_cmd_token = current_cmd_token->next;
    }
	// Afficher les informations de redirection
	while (current_red_token != NULL)
	{
		if (current_red_token->data_type == OUTPUT_TRUNCATE)
			printf("redirection: OUTPUT_TRUNCATE\n");
		else if (current_red_token->data_type == OUTPUT_APPEND)
			printf("redirection: OUTPUT_APPEND\n");
		else if (current_red_token->data_type == REDIRECTION)
			printf("redirection\n");
		else if (current_red_token->data_type == HEREDOC)
			printf("here_doc\n");
		current_red_token = current_red_token->next;
	}
}
