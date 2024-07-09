/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 22:00:32 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/09 22:25:33 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	test_print_ms_env(char **ms_env)
{
	int	i;

	i = 0;
	if (!ms_env)
		return ;
	while (ms_env[i])
	{
		ft_putendl_fd(ms_env[i], STDOUT_FILENO);
		i++;
	}
}
