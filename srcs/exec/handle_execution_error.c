/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:44:59 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/09 11:49:18 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	print_red_error(char *sender, t_token *red)
{
	ft_putstr_fd(sender, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (red != NULL)
		perror(red->option);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	print_cmd_error(char *sender, t_token *cmd)
{
	ft_putstr_fd(sender, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd != NULL)
		perror(cmd->data);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	print_error_and_exit(char *sender, t_token *cmd,
			int status, t_bash *bash)
{
	print_cmd_error(sender, cmd);
	clear_bash_and_exit(&bash, status);
}
