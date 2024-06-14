/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:39:23 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/21 16:33:47 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	check_redirections(t_token *red)
{
	if (check_data_redirection(red->data, red->data_type) == ERROR_REDIRECTION)
		return (ERROR_REDIRECTION);
	if (check_opt_redirection(red->option, red->option_type) == PARSING_ERROR)
		return (PARSING_ERROR);
	return (PARSING_OK);
}

int	check_data_redirection(char *data, int type)
{
	size_t	len;

	len = ft_strlen(data);
	if (type_equal_to(HERESTRING, type) && len > 3)
	{
		if (len == 4)
			print_parsing_error_msg(UNEXPECTED_TOKEN, "<", 0);
		if (len == 5)
			print_parsing_error_msg(UNEXPECTED_TOKEN, "<<", 0);
		if (len >= 6)
			print_parsing_error_msg(UNEXPECTED_TOKEN, "<<<", 0);
		return (ERROR_REDIRECTION);
	}
	if (type_equal_to(OUTPUT_APPEND, type) && len > 2)
	{
		if (len == 3)
			print_parsing_error_msg(UNEXPECTED_TOKEN, ">", 0);
		if (len >= 4)
			print_parsing_error_msg(UNEXPECTED_TOKEN, ">>", 0);
		return (ERROR_REDIRECTION);
	}
	if (type_equal_to(HERESTRING, type))
		return (print_parsing_error_msg(HERESTRING_NOT_IMPLEMENTED, NULL, 0));
	return (PARSING_OK);
}

int	check_opt_redirection(char *option, int type)
{
	int		i;

	i = 0;
	if (!option)
		return (print_parsing_error_msg(UNEXPECTED_TOKEN, "newline", 0));
	if (option[i] == '#')
		return (print_parsing_error_msg(UNEXPECTED_TOKEN, "newline", 0));
	if (unexpected_red_token(option[i]))
		return (print_parsing_error_msg(UNEXPECTED_TOKEN, NULL, option[i]));
	if (type_equal_to(D_QUOTES, type) || type_equal_to(S_QUOTES, type))
	{
		if (check_closed_quotes(option) == PARSING_ERROR)
			return (PARSING_ERROR);
	}
	if (check_text_out_of_quotes(option, unexpected_red_token) == PARSING_ERROR)
		return (PARSING_ERROR);
	return (PARSING_OK);
}

int	unexpected_red_token(char c)
{
	char	*tokens;
	int		i;

	tokens = "()><;&";
	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == c)
			return (PARSING_ERROR);
		i++;
	}
	return (PARSING_OK);
}
