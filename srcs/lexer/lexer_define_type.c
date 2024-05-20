/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_define_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:38:55 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/20 09:12:28 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	define_cmd_token_type(t_token *token, int *cmd)
{
	if (*cmd == 0)
	{
		if (is_builtin(token->data))
			token->data_type |= BUILTIN;
		else
			token->data_type |= CMD;
	}
	else
		token->data_type |= WORD;
	*cmd += 1;
}

void	define_quotes_token_type(int *type, char quote)
{
	if (quote == '\'')
		*type |= S_QUOTES;
	if (quote == '\"')
		*type |= D_QUOTES;
}

void	define_red_token_type(t_token *new, char *sequence, int *i)
{
	if ((sequence[*i] == '<') && (sequence[*i + 1] == '<')
		&& (sequence[*i + 2] == '<'))
	{
		new->data_type |= HERESTRING;
	}
	else if ((sequence[*i] == '<') && (sequence[*i + 1] == '<'))
		new->data_type |= HEREDOC;
	else if ((sequence[*i] == '>') && (sequence[*i + 1] == '>'))
		new->data_type |= OUTPUT_APPEND;
	else if (sequence[*i] == '<')
		new->data_type |= INPUT;
	else if (sequence[*i] == '>')
		new->data_type |= OUTPUT_TRUNCATE;
}
