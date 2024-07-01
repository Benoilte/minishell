/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 21:35:23 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/30 21:47:11 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	add_arg_env(t_bash *bash, t_token *current_arg)
{
	while (ft_strchr(current_arg->data, '=') != NULL && current_arg)
	{
		add_back_env(&bash->env, new_env(current_arg->data));
		current_arg = current_arg->next;
	}
}
