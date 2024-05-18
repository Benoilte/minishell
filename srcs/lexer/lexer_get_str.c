/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:26:05 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/18 16:24:18 by bebrandt         ###   ########.fr       */
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
	*i += 1;
	origin = *i;
	while (sequence[*i] && sequence[*i] != quote)
		*i += 1;
	data = ft_substr(sequence, origin, *i - origin);
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

char	*get_word(t_bash *bash, t_token *new, char *sequence, int *i)
{
	int		origin;
	char	*data;

	origin = *i;
	while (sequence[*i] && ft_isspace(sequence[*i]) == 0)
		*i += 1;
	data = ft_substr(sequence, origin, *i - origin);
	if (!data)
	{
		clear_token(&new);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	return (data);
}
