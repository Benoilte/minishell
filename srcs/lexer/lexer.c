/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:53:37 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/17 18:23:04 by bebrandt         ###   ########.fr       */
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
		if (ft_isspace(sequence[i]))
			i++;
		else if ((sequence[i] == '<') || (sequence[i] == '>'))
			set_redirection(bash, sequence, &i);
		else if ((sequence[i] == '\"') || (sequence[i] == '\''))
			set_quotes(bash, sequence, &i, &cmd);
		else if (sequence[i] == '|')
			set_pipe(bash, &i, &cmd);
		else
			set_word(bash, sequence, &i, &cmd);
	}
}

void	set_redirection(t_bash *bash, char *sequence, int *i)
{
	(void)bash;
	(void)sequence;
	*i += 1;
	ft_printf("set the redirections\n");
}

void	set_quotes(t_bash *bash, char *sequence, int *i, int *cmd)
{
	char	quote;
	int		origin;
	char	*data;
	// t_t

	(void)bash;
	(void)cmd;
	// if (*cmd == 0)
	// 	bash->instruction->cmd->type |= CMD;
	quote = sequence[*i];
	origin = *i;
	*i += 1;
	while (sequence[*i] && sequence[*i] != quote)
		*i += 1;
	data = ft_substr(sequence, origin, (*i - origin) + 1);
	ft_printf("data in quotes: %s\n", data);
	free(data);
	*i += 1;

}

void	set_pipe(t_bash *bash, int *i, int *cmd)
{
	(void)bash;
	(void)cmd;
	*i += 1;
	ft_printf("set the pipe\n");
}

void	set_word(t_bash *bash, char *sequence, int *i, int *cmd)
{
	(void)bash;
	(void)sequence;
	(void)cmd;
	*i += 1;
	ft_printf("set the word\n");
}
