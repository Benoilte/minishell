/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_data_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:03:36 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/12 14:26:27 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_content(void *content)
{
	free(content);
}

int	add_back_recast(t_list **recast, char *value)
{
	t_list	*new;

	new = ft_lstnew(value);
	if (!new)
	{
		if (value)
			free(value);
		return (RETURN_FAILURE);
	}
	ft_lstadd_back(recast, new);
	return (RETURN_SUCCESS);
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

char	*duplicate_data_updated(t_list *recast, int size)
{
	char	*data_updated;
	t_list	*tmp;
	int		i;
	int		k;

	data_updated = (char *)malloc((sizeof(char) * size) + 1);
	if (!data_updated)
		return (NULL);
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

int	fill_cmd_array(t_instruction *instruction, t_token *cmd)
{
	t_token	*tmp;
	int		len;
	int		i;

	len = size_token(cmd);
	instruction->cmd_array = (char **)malloc((sizeof(char *) * (len + 1)));
	if (!instruction->cmd_array)
		return (RETURN_FAILURE);
	i = 0;
	tmp = cmd;
	while (tmp)
	{
		instruction->cmd_array[i] = tmp->data;
		i++;
		tmp = tmp->next;
	}
	instruction->cmd_array[i] = NULL;
	return (RETURN_SUCCESS);
}
