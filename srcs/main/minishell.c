/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:29:53 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/15 23:22:20 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_bash	*bash;

	set_sig_int(IGNORE);
	set_sig_quit(IGNORE);
	init_bash(&bash, envp);
	if (argc == 1)
		start_interactive_minishell(bash, 0);
	else if (argc == 2)
		start_non_interactive_minishell(bash, argv[1], 0);
	else
		print_how_to_use_minishell();
	clear_bash(&bash);
	return (EXIT_SUCCESS);
}

void	print_how_to_use_minishell(void)
{
	ft_printf("\n\t\033[0;31mWRONG ARGUMENT FOR MINISHEL PROGRAM\033[0m\n\n\n");
	ft_printf("	\033[0;32mSTART WITHOUT ARGUMENT `./minishell`\n\n\n");
	ft_printf("	START WITH A FILE ARGUMENT `./minishell test.sh`\033[0m\n\n");
	ft_printf("	\033[0;33mfile argument should be with extension`.sh` ");
	ft_printf("and first line of the file should start with `#! minishell`\n");
	ft_printf("\n\033[0m");
}
