/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:54:25 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/21 14:00:25 by bebrandt         ###   ########.fr       */
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
			get_env_value(bash, recast, src, &i);
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

void	get_env_value(t_bash *bash, t_list **recast, char *data, int *i)
{
	int		origin;
	char	*env_var_name;
	char	*env_var_value;

	*i += 1;
	origin = *i;
	if ((data[*i] == '\0') || (data[*i] == '\''))
		origin -= 1;
	while (data[*i]
		&& ((data[*i] != '$') && (data[*i] != '\'') && (data[*i] != '\"')))
		*i += 1;
	env_var_name = ft_substr(data, origin, *i - origin);
	if (!env_var_name)
	{
		ft_lstclear(recast, &free_content);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	if (ft_strncmp(env_var_name, "$", ft_strlen(env_var_name)) == 0)
	{
		add_back_recast(bash, recast, env_var_name);
		return ;
	}
	env_var_value = get_value(bash, env_var_name);
	free(env_var_name);
	add_back_recast(bash, recast, env_var_value);
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
