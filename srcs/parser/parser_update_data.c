/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:54:25 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/23 15:20:03 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	*update_data(t_bash *bash, char *data)
{
	t_list	*recast;
	int		length_data_updated;
	char	*data_updated;

	recast = NULL;
	filter_data(bash, &recast, data, 0);
	length_data_updated = count_length_data_updated(recast);
	data_updated = duplicate_data_updated(bash, recast, length_data_updated);
	ft_lstclear(&recast, &free_content);
	free(data);
	return (data_updated);
}

void	filter_data(t_bash *bash, t_list **recast, char *src, char quote)
{
	int		i;

	i = 0;
	while (src[i])
	{
		if (src[i] == '$')
		{
			i += 1;
			if (src[i] == '\0' || src[i] == '\'')
				get_dollar_sign(bash, recast, &i);
			else if (src[i] == '?')
				get_last_cmd_exit_status(bash, recast, &i);
			else if (src[i] == '$')
				get_process_id(bash, recast, &i);
			else if (src[i] == '0')
				get_minishell_name(bash, recast, &i);
			else
				get_env_value(bash, recast, src, &i);
		}
		else if (quote != '\"' && ((src[i] == '\'') || (src[i] == '\"')))
			get_text_in_quotes(bash, recast, src, &i);
		else
			get_text_unchanged(bash, recast, src, &i);
	}
}

void	get_text_unchanged(t_bash *bash, t_list **recast, char *src, int *i)
{
	int		origin;
	char	*text_unchanged;

	origin = *i;
	while (src[*i])
	{
		if ((src[*i] == '$') || (src[*i] == '\"'))
			break ;
		else if (!bash->buffer && (src[*i] == '\''))
			break ;
		*i += 1;
	}
	text_unchanged = ft_substr(src, origin, *i - origin);
	if (!text_unchanged)
	{
		ft_lstclear(recast, &free_content);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	add_back_recast(bash, recast, text_unchanged);
}

void	get_text_in_quotes(t_bash *bash, t_list **recast, char *data, int *i)
{
	int			origin;
	char		quote;
	char		*get_text_in_quotes;

	quote = data[*i];
	*i += 1;
	origin = *i;
	while (data[*i] && data[*i] != quote)
		*i += 1;
	get_text_in_quotes = ft_substr(data, origin, *i - origin);
	if (!get_text_in_quotes)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	*i += 1;
	if (quote == '\"')
	{
		bash->buffer = get_text_in_quotes;
		filter_data(bash, recast, bash->buffer, '\"');
		reset_buffer(bash->buffer);
		return ;
	}
	add_back_recast(bash, recast, get_text_in_quotes);
}
