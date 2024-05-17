/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:53:37 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/17 16:39:43 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexing(t_bash *bash, char *sequence)
{
	int	i;
	int	cmd;

	i = 0;
	cmd = 0;
	bash->instruction = new_instruction();
	if (!bash->instruction)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	while (sequence[i])
	{
		if ((sequence[i] == '<') || (sequence[i] == '>'))
			set_redirection(bash, sequence, &i);
		else if ((sequence[i] == '\"') || (sequence[i] == '\''))
			set_quotes(bash, sequence, &i, &cmd);
		else if (sequence[i] == '|')
			set_pipe(bash, &i, &cmd);
		else
			set_word(bash, sequence, &i, &cmd);
		i++;
	}
}

void	set_redirection(t_bash *bash, char *sequence, int *i)
{
	(void)bash;
	(void)sequence;
	(void)i;
	ft_printf("set the redirections\n");
}

void	set_quotes(t_bash *bash, char *sequence, int *i, int *cmd)
{
	(void)bash;
	(void)sequence;
	(void)i;
	(void)cmd;
	ft_printf("set the quotes format\n");
}

void	set_pipe(t_bash *bash, int *i, int *cmd)
{
	(void)bash;
	(void)i;
	(void)cmd;
	ft_printf("set the pipe\n");
}

void	set_word(t_bash *bash, char *sequence, int *i, int *cmd)
{
	(void)bash;
	(void)sequence;
	(void)i;
	(void)cmd;
	ft_printf("set the word\n");
}
