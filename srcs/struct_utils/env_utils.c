/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:53:44 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/24 18:05:45 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value(t_env *env, char *name)
{
	t_env	*tmp;
	int		len;

	tmp = env;
	while (tmp)
	{
		if (ft_strlen(name) > ft_strlen(tmp->name))
			len = ft_strlen(name);
		else
			len = ft_strlen(tmp->name);
		if (ft_strncmp(tmp->name, name, len) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
