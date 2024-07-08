/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:00:59 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/08 17:18:18 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	pwd(t_instruction *instruction)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return ;
	}
	if (instruction->red != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
		printf("%s\n", cwd);
	free(cwd);
}
