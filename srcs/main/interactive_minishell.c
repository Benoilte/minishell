/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_minishell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/10 15:56:27 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_interactive_minishell(t_bash *bash)
{
	while (1)
	{
		bash->sequence = readline("minishell> ");
		if (ft_strlen(bash->sequence) > 0)
			add_history(bash->sequence);
		if (lexing(bash, bash->sequence) == RETURN_SUCCESS)
		{
			if (parsing(bash) == PARSING_OK)
			{
				test_print_instruction(bash->instruction);
			}
		}
		clear_instruction(&(bash)->instruction);
		free(bash->sequence);
		bash->sequence = NULL;
	}
	rl_clear_history();
}
