/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:29:37 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/27 23:05:58 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_env(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

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
