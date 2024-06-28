/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:47:27 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/28 17:19:59 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	update_ms_env(t_bash *bash)
{
	clear_ms_env(bash->ms_env);
	init_ms_env(bash->env);
}
