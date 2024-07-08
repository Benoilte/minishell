/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ben.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:18:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/13 13:16:31 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_bash	*bash;

	init_bash(&bash, envp);
	if (argc == 1)
		start_interactive_minishell(bash, 1);
	else if (argc == 2)
		start_non_interactive_minishell(bash, argv[1], 1);
	else
		print_how_to_use_minishell();
	clear_bash(&bash);
	return (EXIT_SUCCESS);
}

void	print_how_to_use_minishell(void)
{
	ft_printf("description on how to use minishell\n");
}
