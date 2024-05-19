/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:45:29 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/19 12:27:06 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_error_msg(char *cmd, char *msg, char *token)
{
	if (cmd)
		ft_printf("minishell: %s: %s\n", cmd, msg);
	else if (token)
		ft_printf("minishell: %s `%s' \n", msg, token);
	else
		ft_printf("minishell: %s\n", msg);
	return (1);
}
