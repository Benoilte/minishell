/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tom.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:29:38 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/23 15:52:29 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_bash	*bash;

	(void)argv;
	if (argc != 1)
		ft_printf("run the program without argument as follow: ./minishell\n");
	else
	{
		init_bash(&bash, envp);
		while (1)
		{
			bash->sequence = readline("minishell> ");
			if (ft_strlen(bash->sequence) == 0)
				printf("%s", bash->sequence);
			else
			{
				add_history(bash->sequence);
				lexing(bash, bash->sequence);
				if (parsing(bash) == 0)
				{
					test_print_instruction(bash->instruction);
				}
				exec(bash->instruction);
				// test_print_instruction(bash->instruction);
				clear_instruction(&(bash)->instruction);
			}
			free(bash->sequence);
			bash->sequence = NULL;		
		}
		rl_clear_history();
		clear_bash(&bash);
	}
	return (EXIT_SUCCESS);
}
