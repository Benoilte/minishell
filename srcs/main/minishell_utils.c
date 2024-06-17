/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:48:49 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/17 18:41:53 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	type_equal_to(int flag, int type)
{
	return ((type & flag) == flag);
}

void	check_sequence_and_execution(t_bash *bash, int debug)
{
	if (lexing(bash, bash->sequence) == RETURN_SUCCESS
		&& sequence_is_filled(bash->instruction))
	{
		bash->exit_code = parsing(bash);
		if (bash->exit_code == SYNTAX_OK)
		{
			if (debug)
				test_print_instruction(bash->instruction);
			exec(bash->instruction, bash, bash->envp);
		}
	}
}
