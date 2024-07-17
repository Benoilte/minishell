/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:48:49 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/15 23:58:27 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	type_equal_to(int flag, int type)
{
	return ((type & flag) == flag);
}

void	check_sequence_and_execution(t_bash *bash, int debug)
{
	int	exit_status;

	if (lexing(bash, bash->sequence) == RETURN_SUCCESS
		&& sequence_is_filled(bash->instruction))
	{
		if (g_signal_code)
		{
			bash->exit_code = 128 + g_signal_code;
			g_signal_code = 0;
		}
		exit_status = parsing(bash);
		if (exit_status == SYNTAX_OK)
		{
			if (debug)
				test_print_instruction(bash->instruction);
			exec(bash->instruction, bash);
		}
		else
			bash->exit_code = exit_status;
	}
}
