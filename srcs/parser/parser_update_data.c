/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:54:25 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/21 09:35:29 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	update_data(t_bash *bash, char *data)
{
	t_list	*recast;

	recast = NULL;
	filter_data(bash, &recast, data, 0);
	while (recast)
	{
		if (recast->content)
			ft_printf("%s", recast->content);
		recast = recast->next;
	}
	ft_printf("\n");
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
	t_list	*new;

	origin = *i;
	while (src[*i]
		&& ((src[*i] != '$') && (src[*i] != '\'') && (src[*i] != '\"')))
		*i += 1;
	text_unchanged = ft_substr(src, origin, *i - origin);
	if (!text_unchanged)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	new = ft_lstnew(text_unchanged);
	if (!new)
	{
		free(text_unchanged);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	ft_lstadd_back(recast, new);
}

void	get_env_value(t_bash *bash, t_list **recast, char *data, int *i)
{
	int		origin;
	char	*env_var_name;
	char	*env_var_value;
	t_list	*new;

	*i += 1;
	origin = *i;
	while (data[*i]
		&& ((data[*i] != '$') && (data[*i] != '\'') && (data[*i] != '\"')))
		*i += 1;
	env_var_name = ft_substr(data, origin, *i - origin);
	if (!env_var_name)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	env_var_value = get_value(bash, env_var_name);
	free(env_var_name);
	new = ft_lstnew(env_var_value);
	if (!new)
	{
		free(env_var_value);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	ft_lstadd_back(recast, new);
}

void	get_text_in_quotes(t_bash *bash, t_list **recast, char *data, int *i)
{
	int			origin;
	char		quote;
	t_list		*new;

	quote = data[*i];
	*i += 1;
	origin = *i;
	while (data[*i] && data[*i] != quote)
		*i += 1;
	bash->buffer = ft_substr(data, origin, *i - origin);
	if (!bash->buffer)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	*i += 1;
	if (quote == '\"')
	{
		filter_data(bash, recast, bash->buffer, '\"');
		free(bash->buffer);
		bash->buffer = NULL;
		return ;
	}
	new = ft_lstnew(bash->buffer);
	if (!new)
	{
		free(bash->buffer);
		bash->buffer = NULL;
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	ft_lstadd_back(recast, new);
}
