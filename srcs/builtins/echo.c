/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:54:13 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/27 11:13:23 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	echo(t_instruction *instruciton)
{
	int	start_index;
	int	new_line;
	int	i;

	new_line = 1;
	start_index = 1;
	if (instruciton->cmd_array[1] != NULL
		&& ft_strncmp(instruciton->cmd_array[1], "-n", 2) == 0)
	{
		new_line = 0;
		start_index = 2;
	}
	i = start_index;
	while (instruciton->cmd_array[i] != NULL)
	{
		printf("%s", instruciton->cmd_array[i]);
		if (instruciton->cmd_array[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
}
