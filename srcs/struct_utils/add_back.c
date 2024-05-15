/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:31:19 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/15 12:13:29 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_back_env(t_env **env, t_env *new)
{
	t_env	*last;

	if (!env || !new)
		return ;
	last = last_env(*env);
	if (!*env)
		*env = new;
	else
		last->next = new;
}
