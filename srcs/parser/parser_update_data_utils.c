/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_data_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:03:36 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/21 12:08:20 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_content(void *content)
{
	free(content);
}

void	add_back_recast(t_bash *bash, t_list **recast, char *value)
{
	t_list	*new;

	new = ft_lstnew(value);
	if (!new)
	{
		if (value)
			free(value);
		ft_lstclear(recast, &free_content);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	ft_lstadd_back(recast, new);
}

int	count_length_data_updated(t_list *recast)
{
	t_list	*tmp;
	int		i;
	int		len;

	tmp = recast;
	len = 0;
	while (tmp)
	{
		i = 0;
		while (((char *)(tmp->content))[i])
		{
			i++;
			len++;
		}
		tmp = tmp->next;
	}
	return (len);
}

char	*duplicate_data_updated(t_bash *bash, t_list *recast, int size)
{
	char	*data_updated;
	t_list	*tmp;
	int		i;
	int		k;

	data_updated = (char *)malloc((sizeof(char) * size) + 1);
	if (!data_updated)
	{
		ft_lstclear(&recast, &free_content);
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	}
	tmp = recast;
	k = 0;
	while (tmp)
	{
		i = 0;
		while (((char *)(tmp->content))[i])
			data_updated[k++] = ((char *)(tmp->content))[i++];
		tmp = tmp->next;
	}
	data_updated[k] = '\0';
	return (data_updated);
}
