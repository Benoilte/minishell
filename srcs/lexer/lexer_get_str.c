/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:26:05 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/21 08:23:20 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

char	*get_text_data(t_bash *bash, t_token *new, int *type, int *i)
{
	int		origin;
	char	*data;
	char	*sequence;

	sequence = bash->sequence;
	origin = *i;
	while (sequence[*i] && (ft_isspace(sequence[*i]) == 0)
		&& sequence[*i] != '<' && sequence[*i] != '>' && sequence[*i] != '|')
	{
		if ((sequence[*i] == '\"') || (sequence[*i] == '\''))
		{
			define_quotes_token_type(type, sequence[*i]);
			move_to_next_quote(sequence[*i], sequence, i);
		}
		if (sequence[*i])
			*i += 1;
	}
	if (*i == origin)
		return (NULL);
	data = get_substr_or_exit(bash, new, origin, *i);
	return (data);
}

void	move_to_next_quote(char quote, char *sequence, int *i)
{
	quote = sequence[*i];
	*i += 1;
	while (sequence[*i] && sequence[*i] != quote)
		*i += 1;
}

char	*get_redirection_data(t_bash *bash, t_token *new, int *i)
{
	int		origin;
	char	red_sign;
	char	*data;
	char	*sequence;

	sequence = bash->sequence;
	red_sign = sequence[*i];
	origin = *i;
	while (sequence[*i] == red_sign)
		*i += 1;
	data = get_substr_or_exit(bash, new, origin, *i);
	return (data);
}

char	*get_one_char_token(t_bash *bash, t_token *new, char *sequence, int *i)
{
	char	*data;

	data = ft_substr(sequence, *i, 1);
	if (!data)
	{
		clear_token(&new);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	*i += 1;
	return (data);
}

char	*get_substr_or_exit(t_bash *bash, t_token *new, int start, int i)
{
	char	*data;

	data = ft_substr(bash->sequence, start, i - start);
	if (!data)
	{
		clear_token(&new);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	return (data);
}
