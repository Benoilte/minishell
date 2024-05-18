/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:31:11 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/18 10:14:50 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*last_env(t_env *env)
{
	t_env	*last;

	if (!env)
		return (NULL);
	last = env;
	while (last->next)
		last = last->next;
	return (last);
}

t_instruction	*last_instruction(t_instruction *inst)
{
	t_instruction	*last;

	if (!inst)
		return (NULL);
	last = inst;
	while (last->next)
		last = last->next;
	return (last);
}

t_token	*last_token(t_token *token)
{
	t_token	*last;

	if (!token)
		return (NULL);
	last = token;
	while (last->next)
		last = last->next;
	return (last);
}
