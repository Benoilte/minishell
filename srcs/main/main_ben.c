/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ben.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:18:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/18 11:46:21 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_bash	*bash;
	char	*sequence;
	int		input_is_not_exit;

	(void)argv;
	if (argc != 1)
		ft_printf("run the program without argument as follow: ./minishell\n");
	else
	{
		init_bash(&bash, envp);
			input_is_not_exit = 1;
		while (input_is_not_exit)
		{
			sequence = readline("minishell> ");
			if (ft_strlen(sequence) == 0)
				printf("%s", sequence);
			else if (ft_strncmp(sequence, "exit", ft_strlen(sequence)) == 0)
				break ;
			else if (ft_strncmp(sequence, "env", ft_strlen(sequence)) == 0)
				test_print_env(bash->env);
			else
			{
				add_history(sequence);
				lexing(bash, sequence);
				test_print_cmd_token(bash->instruction->cmd);
				clear_instruction(&(bash)->instruction);
			}
			free(sequence);		
		}
		rl_clear_history();
		free (sequence);
		clear_bash(&bash);
	}
	return (EXIT_SUCCESS);
}
