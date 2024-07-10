/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:25:32 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/10 21:05:48 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*clear_bash_and_exit(t_bash **bash, int exit_code)
{
	if (isatty(STDIN_FILENO))
		set_terminal(RESET);
	clear_bash(bash);
	exit(exit_code);
}

void	*clear_bash(t_bash **bash)
{
	if ((*bash)->working_directory)
		free((*bash)->working_directory);
	if ((*bash)->sequence)
		free((*bash)->sequence);
	if ((*bash)->instruction)
		clear_instruction(&(*bash)->instruction);
	if ((*bash)->env)
		clear_env(&(*bash)->env);
	if ((*bash)->ms_env)
		clear_ms_env((*bash)->ms_env);
	free(*bash);
	return (NULL);
}
