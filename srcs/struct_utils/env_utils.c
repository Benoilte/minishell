/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:53:44 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/21 13:51:24 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value(t_bash *bash, char *name)
{
	t_env	*tmp;
	char	*value;

	tmp = bash->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(tmp->name)) == 0)
		{
			value = ft_strdup(tmp->value);
			if (!value)
			{
				free(name);
				clear_bash_and_exit(&bash, EXIT_FAILURE);
			}
			return (value);
		}
		tmp = tmp->next;
	}
	value = ft_strdup("");
	return (value);
}