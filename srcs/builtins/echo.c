/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tommartinelli <tommartinelli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:54:13 by tmartin2          #+#    #+#             */
/*   Updated: 2024/07/08 17:32:59 by tommartinel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	check_echo_arg(char *arg)
{
	int	j;

	if (arg[0] == '-')
	{
		j = 1;
		while (arg[j] != '\0')
		{
			if (arg[j] != 'n')
				return (1);
			j++;
		}
		return (0);
	}
	return (1);
}

int	handle_echo_options(t_instruction *instruction)
{
	if (instruction->cmd_array[1] != NULL
		&& ft_strncmp(instruction->cmd_array[1], "-n", 2) == 0)
		return (2);
	return (1);
}

void	print_echo_args(t_instruction *instruction, int start_index)
{
	int		print_first_arg;
	int		i;

	print_first_arg = 0;
	i = start_index;
	while (instruction->cmd_array[i] != NULL)
	{
		if (print_first_arg == 0)
			print_first_arg = check_echo_arg(instruction->cmd_array[i]);
		if (print_first_arg == 1)
		{
			ft_putstr_fd(instruction->cmd_array[i], STDOUT_FILENO);
			if (instruction->cmd_array[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		i++;
	}
}

void	echo(t_instruction *instruction)
{
	int	start_index;
	int	new_line;

	new_line = 1;
	start_index = handle_echo_options(instruction);
	if (start_index == 2)
		new_line = 0;
	print_echo_args(instruction, start_index);
	if (new_line)
	{
		if (instruction->red != NULL)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else
			printf("\n");
	}
}
