/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:49:57 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/17 18:47:56 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	print_parsing_error_msg(char *msg, char *token_str, char token_c)
{
	if (token_str)
		ft_printf("minishell: %s `%s' \n", msg, token_str);
	else if (token_c != '\0')
		ft_printf("minishell: %s `%c' \n", msg, token_c);
	else
		ft_printf("minishell: %s\n", msg);
	return (SYNTAX_ERROR);
}

int	check_closed_quotes(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
			data = ft_strchr(data + (i + 1), data[i]);
			i = 0;
			if (!data)
			{
				print_parsing_error_msg(UNCLOSED_QUOTES, NULL, 0);
				return (SYNTAX_ERROR);
			}
		}
		i++;
	}
	return (SYNTAX_OK);
}

int	check_text_out_of_quotes(char *data, int (*is_unexpected_token)(char))
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
			data = ft_strchr(data + (i + 1), data[i]);
			i = 0;
		}
		if (is_unexpected_token(data[i]))
		{
			print_parsing_error_msg(UNEXPECTED_TOKEN, NULL, data[i]);
			return (SYNTAX_ERROR);
		}
		i++;
	}
	return (SYNTAX_OK);
}
