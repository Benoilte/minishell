/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:25:32 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/12 09:21:25 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	if ((*bash)->sequence)
		free((*bash)->sequence);
	if ((*bash)->instruction)
		clear_instruction(&(*bash)->instruction);
	if ((*bash)->env)
		clear_env(&(*bash)->env);
	if ((*bash)->ms_env)
		clear_ms_env((*bash)->ms_env);
	if ((*bash)->fd_arg_file != -1)
		close((*bash)->fd_arg_file);
	free(*bash);
	return (NULL);
}
