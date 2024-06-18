/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:49:24 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/17 18:50:43 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	check_cmd(t_token *cmd)
{
	if (check_data_cmd(cmd->data, cmd->data_type) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (SYNTAX_OK);
}

int	check_data_cmd(char *data, int type)
{
	if (type_equal_to(D_QUOTES, type) || type_equal_to(S_QUOTES, type))
	{
		if (check_closed_quotes(data) == SYNTAX_ERROR)
			return (SYNTAX_ERROR);
	}
	if (check_text_out_of_quotes(data, unexpected_cmd_token) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (SYNTAX_OK);
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
