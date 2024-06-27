/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:53:44 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/25 22:22:25 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*get_name_to_value(char *name, char *value)
{
	int		i;
	int		j;
	size_t	len;
	char	*name_to_value;

	len = ft_strlen(name);
	len += ft_strlen(value);
	len += 2;
	name_to_value = (char *)ft_calloc(len, sizeof(char));
	if (!name_to_value)
		return (NULL);
	i = -1;
	while (name[++i])
		name_to_value[i] = name[i];
	name_to_value[i] = '=';
	i++;
	j = 0;
	while (value[j])
		name_to_value[i++] = value[j++];
	name_to_value[i] = '\0';
	return (name_to_value);
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
