/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:54:25 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/24 16:55:02 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	*update_data(t_bash *bash, char *data)
{
	t_list	*recast;
	int		length_data_updated;
	char	*data_updated;

	recast = NULL;
	if (filter_data(bash, &recast, data, 0) == RETURN_FAILURE)
	{
		ft_lstclear(&recast, &free_content);
		return (NULL);
	}
	length_data_updated = count_length_data_updated(recast);
	data_updated = duplicate_data_updated(recast, length_data_updated);
	ft_lstclear(&recast, &free_content);
	free(data);
	if (!data_updated)
		return (NULL);
	return (data_updated);
}

int	filter_data(t_bash *bash, t_list **recast, char *src, char quote)
{
	int		i;
	int		return_status;

	i = 0;
	return_status = RETURN_SUCCESS;
	while ((return_status == RETURN_SUCCESS) && src[i])
	{
		if (src[i] == '$')
			return_status = filter_expansion(bash, recast, src, &i);
		else if (quote != '\"' && ((src[i] == '\'') || (src[i] == '\"')))
			return_status = get_text_in_quotes(bash, recast, src, &i);
		else
			return_status = get_text_unchanged(recast, src, &i, quote);
	}
	return (return_status);
}

int	filter_expansion(t_bash *bash, t_list **recast, char *src, int *i)
{
	*i += 1;
	if (src[*i] == '\0' || src[*i] == '\'')
		return (get_dollar_sign(recast));
	else if (src[*i] == '?')
		return (get_last_cmd_exit_status(recast, i, bash->exit_code));
	else if (src[*i] == '$')
		return (get_process_id(recast, i));
	else if (src[*i] == '0')
		return (get_minishell_name(recast, i));
	else
		return (get_env_value(recast, bash->env, src, i));
}

int	get_text_unchanged(t_list **recast, char *src, int *i, char quote)
{
	int		origin;
	char	*text_unchanged;

	origin = *i;
	while (src[*i])
	{
		if ((src[*i] == '$') || (src[*i] == '\"'))
			break ;
		else if (quote != '\"' && (src[*i] == '\''))
			break ;
		*i += 1;
	}
	text_unchanged = ft_substr(src, origin, *i - origin);
	if (!text_unchanged)
		return (RETURN_FAILURE);
	return (add_back_recast(recast, text_unchanged));
}

int	get_text_in_quotes(t_bash *bash, t_list **recast, char *data, int *i)
{
	int			origin;
	char		quote;
	char		*text_in_quotes;

	quote = data[*i];
	*i += 1;
	origin = *i;
	while (data[*i] && data[*i] != quote)
		*i += 1;
	text_in_quotes = ft_substr(data, origin, *i - origin);
	if (!text_in_quotes)
		return (RETURN_FAILURE);
	*i += 1;
	if (quote == '\"')
	{
		if (filter_data(bash, recast, text_in_quotes, '\"') == RETURN_FAILURE)
		{
			free(text_in_quotes);
			return (RETURN_FAILURE);
		}
		return (RETURN_SUCCESS);
	}
	return (add_back_recast(recast, text_in_quotes));
}
