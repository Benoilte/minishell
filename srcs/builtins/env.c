/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:42:09 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/11 14:46:45 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void print_env(t_env *env, t_instruction *instruction)
{
	t_env	*tmp;

	tmp = env;
    
	while (tmp)
	{
		if (instruction->red != NULL)
		{
            ft_putstr_fd(tmp->name, STDOUT_FILENO);
            ft_putstr_fd("=", STDOUT_FILENO);
            ft_putendl_fd(tmp->value, STDOUT_FILENO);
		}
		else
			ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	exit(EXIT_SUCCESS);
}

