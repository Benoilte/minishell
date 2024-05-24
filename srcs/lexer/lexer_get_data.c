/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:26:05 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/24 14:24:53 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

char	*get_text_data(char *sequence, int *i, int *type)
{
	int		origin;
	char	*data;

	origin = *i;
	while (sequence[*i] && (ft_isspace(sequence[*i]) == 0)
		&& sequence[*i] != '<' && sequence[*i] != '>' && sequence[*i] != '|')
	{
		if ((sequence[*i] == '\"') || (sequence[*i] == '\''))
		{
			define_quotes_token_type(type, sequence[*i]);
			move_to_next_quote(sequence, i);
		}
		if (sequence[*i])
			*i += 1;
	}
	if (*i == origin)
		return (ft_strdup(""));
	data = ft_substr(sequence, origin, *i - origin);
	if (!data)
		return (NULL);
	return (data);
}

char	*get_redirection_data(char *sequence, int *i)
{
	int		origin;
	char	red_sign;
	char	*data;

	red_sign = sequence[*i];
	origin = *i;
	while (sequence[*i] == red_sign)
		*i += 1;
	data = ft_substr(sequence, origin, *i - origin);
	if (!data)
		return (NULL);
	return (data);
}
