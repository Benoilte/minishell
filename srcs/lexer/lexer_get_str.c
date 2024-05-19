/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:26:05 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/18 22:25:07 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_data_in_quotes(t_bash *bash, t_token *new, char *sequence, int *i)
{
	int		quote;
	int		origin;
	char	*data;

	new->n_quotes++;
	quote = sequence[*i];
	origin = *i;
	*i += 1;
	while (sequence[*i] && sequence[*i] != quote)
		*i += 1;
	data = ft_substr(sequence, origin, (*i - origin) + 1);
	if (!data)
	{
		clear_token(&new);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	if (sequence[*i] == quote)
	{
		new->n_quotes++;
		*i += 1;
	}
	return (data);
}

char	*get_text(t_bash *bash, t_token *new, int *type, int *i)
{
	int		origin;
	char	*data;
	char	*sequence;

	sequence = bash->sequence;
	origin = *i;
	while (sequence[*i] && ft_isspace(sequence[*i]) == 0
		&& sequence[*i] != '<' && sequence[*i] != '>')
	{
		if ((sequence[*i] == '\"') || (sequence[*i] == '\''))
		{
			define_quotes_token_type(type, sequence[*i]);
			move_to_next_quote(sequence[*i], sequence, i);
		}
		if (sequence[*i])
			*i += 1;
	}
	data = ft_substr(sequence, origin, *i - origin);
	if (!data)
	{
		clear_token(&new);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
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
	data = ft_substr(sequence, origin, *i - origin);
	if (!data)
	{
		clear_token(&new);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	return (data);
}
