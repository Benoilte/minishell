/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:39:23 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/19 13:16:18 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redirections(t_token *red)
{
	if (check_data_redirection(red->data, red->data_type) == PARSING_ERROR)
		return (PARSING_ERROR);
	if (check_opt_redirection(red->option, red->option_type) == PARSING_ERROR)
		return (PARSING_ERROR);
	return (PARSING_OK);
}

int	check_data_redirection(char *data, int type)
{
	size_t	len;

	len = ft_strlen(data);
	if (((type & HERESTRING) == HERESTRING) && len > 3)
	{
		if (len == 4)
			print_parsing_error_msg(UNEXPECTED_TOKEN, "<");
		if (len == 5)
			print_parsing_error_msg(UNEXPECTED_TOKEN, "<<");
		if (len >= 6)
			print_parsing_error_msg(UNEXPECTED_TOKEN, "<<<");
		return (PARSING_ERROR);
	}
	if (((type & OUTPUT_APPEND) == OUTPUT_APPEND) && len > 2)
	{
		if (len == 3)
			print_parsing_error_msg(UNEXPECTED_TOKEN, ">");
		if (len >= 4)
			print_parsing_error_msg(UNEXPECTED_TOKEN, ">>");
		return (PARSING_ERROR);
	}
	if ((type & HERESTRING) == HERESTRING)
		return (print_parsing_error_msg(HERESTRING_NOT_IMPLEMENTED, NULL));
	return (PARSING_OK);
}

int	check_opt_redirection(char *option, int type)
{
	(void)option;
	(void)type;
	return (PARSING_OK);
}
