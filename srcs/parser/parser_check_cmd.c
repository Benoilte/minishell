/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:49:24 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/20 14:14:17 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/*
& ( ) ;
*/

int	check_cmd(t_token *cmd)
{
	if (check_data_cmd(cmd->data, cmd->data_type) == PARSING_ERROR)
		return (PARSING_ERROR);
	return (PARSING_OK);
}

int	check_data_cmd(char *data, int type)
{
	if (type_equal_to(D_QUOTES, type) || type_equal_to(S_QUOTES, type))
	{
		if (check_closed_quotes(data) == PARSING_ERROR)
			return (PARSING_ERROR);
	}
	if (check_text_out_of_quotes(data, unexpected_cmd_token) == PARSING_ERROR)
		return (PARSING_ERROR);
	return (PARSING_OK);
}

int	unexpected_cmd_token(char c)
{
	char	*tokens;
	int		i;

	tokens = "();&";
	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == c)
			return (1);
		i++;
	}
	return (0);
}