/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ben.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:18:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/24 11:36:38 by bebrandt         ###   ########.fr       */
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
			else if (ft_strncmp(bash->sequence, "exit", ft_strlen(bash->sequence)) == 0)
				break ;
			else if (ft_strncmp(bash->sequence, "env", ft_strlen(bash->sequence)) == 0)
				test_print_env(bash->env);
			else
			{
				add_history(bash->sequence);
				if (lexing(bash, bash->sequence) == RETURN_SUCCESS)
				{
					if (parsing(bash) == 0)
					{
						test_print_instruction(bash->instruction);
					}
				}
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
