/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:12:33 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/08 17:15:10 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	delete_env_node(t_env **env, t_env *prev, t_env *current)
{
	if (prev == NULL)
	{
		*env = current->next;
	}
	else
	{
		prev->next = current->next;
	}
	free(current->name);
	free(current->value);
	free(current);
}

void	ft_unset(t_env **env, t_instruction *instruction)
{
	char	*arg;
	t_env	*current;
	t_env	*prev;
	int		i;

	i = 1;
	while (instruction->cmd_array[i] != NULL)
	{
		arg = instruction->cmd_array[i];
		current = *env;
		prev = NULL;
		while (current)
		{
			if (ft_strcmp(current->name, arg) == 0)
			{
				delete_env_node(env, prev, current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
}
