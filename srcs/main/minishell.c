/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:29:53 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/10 16:02:41 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_bash	*bash;

	init_bash(&bash, envp);
	if (argc == 1)
		start_interactive_minishell(bash);
	else if (argc == 2)
		start_non_interactive_minishell(bash, argv[1]);
	else
		print_how_to_use_minishell();
	clear_bash(&bash);
	return (EXIT_SUCCESS);
}

void	print_how_to_use_minishell(void)
{
	ft_printf("description on how to use minishell\n");
}
