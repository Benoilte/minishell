/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:35:11 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/07 13:11:34 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	sort_red(t_instruction *instruction, t_env *env)
{
	int		i;
	t_token	*current_red_token;
	(void)env;
	i = 0;
	current_red_token = instruction->red;
	// Afficher les informations de redirection
	while (current_red_token != NULL)
	{
		if (current_red_token->data_type == OUTPUT_TRUNCATE
			|| current_red_token->data_type == OUTPUT_APPEND
			|| current_red_token->data_type == INPUT)
			red(instruction);
		else if (current_red_token->data_type == HEREDOC)
			here_doc(instruction);
		current_red_token = current_red_token->next;
	}
}
