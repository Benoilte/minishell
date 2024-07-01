/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:47:27 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/01 06:40:26 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_ms_env(t_bash *bash)
{
	bash->ms_env = clear_ms_env(bash->ms_env);
	bash->ms_env = init_ms_env(bash->env);
}
