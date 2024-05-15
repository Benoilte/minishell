/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:30:56 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/15 13:01:01 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// name_to_value should be equal to name=value || name= || name
t_env	*new_env(char *name_to_value)
{
	t_env	*env;
	int		i;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	i = 0;
	while (name_to_value[i] && name_to_value[i] != '=')
		i++;
	env->name = ft_substr(name_to_value, 0, i);
	if (!env->name)
	{
		free(env);
		return (NULL);
	}
	env->value = ft_substr(name_to_value, i, ft_strlen(name_to_value) - i);
	if (!env->value)
	{
		free(env->name);
		free(env);
		return (NULL);
	}
	env->next = NULL;
	return (env);
}

