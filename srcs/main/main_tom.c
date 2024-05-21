/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tom.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:29:38 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/21 15:07:38 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_bash *bash;

	(void)argv;
	if (argc != 1)
		printf("Error : trop d'argument\n");
	else
	{
		init_bash(&bash, envp);
		while (1)
		{
			bash->sequence = readline("minishell> ");
			if (ft_strlen(bash->sequence) == 0)
				printf("%s", bash->sequence);
			builtins(bash);
			exec(bash, envp);
			add_history(bash->sequence);
			free(bash->sequence);
			bash->sequence = NULL;		
		}
		rl_clear_history();
		clear_bash(&bash);
	}
	return (0);
}
