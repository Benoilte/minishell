/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 11:45:29 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/19 13:05:29 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_parsing_error_msg(char *msg, char *token)
{
	if (token)
		ft_printf("minishell: %s `%s' \n", msg, token);
	else
		ft_printf("minishell: %s\n", msg);
	return (1);
}
