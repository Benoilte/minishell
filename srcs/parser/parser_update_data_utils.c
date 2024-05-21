/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_data_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:03:36 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/21 10:51:57 by bebrandt         ###   ########.fr       */
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
