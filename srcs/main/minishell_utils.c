/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:48:49 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/18 08:34:59 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	type_equal_to(int flag, int type)
{
	return ((type & flag) == flag);
}

int	is_builtin(char *word)
{
	if (ft_strlen(word) == 0)
		return (0);
	if (ft_my_strcmp(word, "echo") == 0)
		return (1);
	if (ft_my_strcmp(word, "cd") == 0)
		return (1);
	if (ft_my_strcmp(word, "pwd") == 0)
		return (1);
	if (ft_my_strcmp(word, "export") == 0)
		return (1);
	if (ft_my_strcmp(word, "unset") == 0)
		return (1);
	if (ft_my_strcmp(word, "env") == 0)
		return (1);
	if (ft_my_strcmp(word, "exit") == 0)
		return (1);
	return (0);
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
