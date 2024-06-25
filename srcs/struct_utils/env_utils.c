/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:53:44 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/25 17:37:30 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

char	*get_value(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (names_are_the_same(tmp->name, name))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

int	name_exist(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (names_are_the_same(tmp->name, name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	names_are_the_same(char *name, char *name_to_check)
{
	int	len;

	if (ft_strlen(name) > ft_strlen(name_to_check))
		len = ft_strlen(name);
	else
		len = ft_strlen(name_to_check);
	return (ft_strncmp(name_to_check, name, len) == 0);
}

void	update_value(t_env *env, char *name, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (names_are_the_same(tmp->name, name))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
}
