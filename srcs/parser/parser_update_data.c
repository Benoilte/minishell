/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:54:25 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/20 19:14:54 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	update_data(t_bash *bash, char *data)
{
	int		start;
	int		i;
	t_list	*data_updated;

	data_updated = NULL;
	i = 0;
	start = 0;
	while (data[i])
	{
		if (data[i] == '$')
		{
			get_text_out_of_quotes(bash, &data_updated, data + start, i - start);
			get_environnemnt_var(bash, &data_updated, data, &i);
			start = i;
		}
		else if ((data[i] == '\'') || (data[i] == '\"'))
		{
			get_text_out_of_quotes(bash, &data_updated, data + start, i - start);
			i++;
			// get_data_in_quotes(bash, data_updated, data, &i);
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		get_text_out_of_quotes(bash, &data_updated, data + start, i - start);
	while (data_updated)
	{
		if (data_updated->content)
			ft_printf("%s", data_updated->content);
		data_updated = data_updated->next;
	}
	ft_printf("\n");
}

void	get_text_out_of_quotes(t_bash *bash, t_list **data_updated, char *src, int len)
{
	char	*text_out_of_quotes;
	t_list	*new;

	ft_printf("len: %d\n", len);
	if (len == 0)
		return ;
	text_out_of_quotes = ft_substr(src, 0, len);
	if (!text_out_of_quotes)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	new = ft_lstnew(text_out_of_quotes);
	if (!new)
	{
		free(text_out_of_quotes);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	ft_lstadd_back(data_updated, new);
}

void	get_environnemnt_var(t_bash *bash, t_list **data_updated, char *data, int *i)
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
	ft_lstadd_back(data_updated, new);
}
