/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:54:16 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/12 18:05:43 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// bash: export: `heloo-=123': not a valid identifier

void	print_export_error_identifier(char *name_to_value)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(name_to_value, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}
