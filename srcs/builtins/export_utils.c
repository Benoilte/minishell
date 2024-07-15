/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:54:16 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/15 23:21:04 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// bash: export: `heloo-=123': not a valid identifier

t_env	**sort_export_env(t_env *env)
{
	t_env	**sorted_env;
	int		unsorted;
	int		i;

	sorted_env = ft_calloc((size_env(env) + 1), sizeof(t_env *));
	if (!sorted_env)
		return (NULL);
	fill_sorted_env(env, sorted_env);
	unsorted = size_env(env);
	while ((unsorted - 1))
	{
		i = 0;
		while (i < (unsorted - 1))
		{
			if (ft_my_strcmp((sorted_env[i])->name, (sorted_env[i + 1])->name)
				> 0)
				swap_export_env(sorted_env, i, i + 1);
			i++;
		}
		unsorted--;
	}
	return (sorted_env);
}

void	fill_sorted_env(t_env *env, t_env **sorted_env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		sorted_env[i] = tmp;
		i++;
		tmp = tmp->next;
	}
	sorted_env[i] = NULL;
}

void	swap_export_env(t_env **sorted_env, int pos_1, int pos_2)
{
	t_env	*tmp_env;

	tmp_env = sorted_env[pos_1];
	sorted_env[pos_1] = sorted_env[pos_2];
	sorted_env[pos_2] = tmp_env;
}

void	print_export_error_identifier(char *name_to_value)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(name_to_value, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}
