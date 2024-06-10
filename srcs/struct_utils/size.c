/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:29:37 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/10 17:08:48 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_instruction(t_instruction *instruction)
{
	int				i;
	t_instruction	*tmp;

	i = 0;
	tmp = instruction;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	size_token(t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
