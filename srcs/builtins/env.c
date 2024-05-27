/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:42:09 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/27 11:34:15 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
    
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

