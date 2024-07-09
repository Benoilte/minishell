/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:16:17 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/09 12:23:26 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	open_file(char *red, t_token *token)
{
	int	file;

	file = -1;
	if (OUTPUT_TRUNCATE & token->data_type)
		file = open(red, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (OUTPUT_APPEND & token->data_type)
		file = open(red, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (INPUT & token->data_type)
		file = open(red, O_RDONLY);
	if (file < 0)
		print_red_error("minishell", token);
	return (file);
}

int	red(t_token *current_red)
{
	char	*red;
	int		file;
	int		i;

	file = 0;
	i = current_red->data_type;
	red = current_red->option;
	if (i & (OUTPUT_TRUNCATE | OUTPUT_APPEND))
	{
		file = open_file(red, current_red);
		if (file < 0)
			return (-1);
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	if (i & INPUT)
	{
		file = open_file(red, current_red);
		if (file < 0)
			return (-1);
		dup2(file, STDIN_FILENO);
		close(file);
	}
	return (0);
}
