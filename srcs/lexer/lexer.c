/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:53:37 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/20 11:53:06 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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
		else if (sequence[i] == '|')
			set_pipe(bash, &i, &cmd);
		else
			set_text_token(bash, sequence, &i, &cmd);
	}
}

// void	set_quotes(t_bash *bash, char *sequence, int *i, int *cmd)
// {
// 	t_token			*new;
// 	t_instruction	*last_inst;

// 	new = init_token(bash);
// 	define_quotes_token_type(&(new->data_type), sequence[*i]);
// 	new->data = get_data_in_quotes(bash, new, sequence, i);
// 	define_cmd_token_type(new, cmd);
// 	last_inst = last_instruction(bash->instruction);
// 	add_back_token(&(last_inst->cmd), new);
// }

void	set_pipe(t_bash *bash, int *i, int *cmd)
{
	t_instruction	*new;

	new = init_instruction(bash);
	add_back_instruction(&(bash->instruction), new);
	*cmd = 0;
	*i += 1;
}

void	set_text_token(t_bash *bash, char *sequence, int *i, int *cmd)
{
	t_token			*new;
	t_instruction	*last_inst;

	(void)sequence;
	new = init_token(bash);
	new->data = get_text_data(bash, new, &(new->data_type), i);
	define_cmd_token_type(new, cmd);
	last_inst = last_instruction(bash->instruction);
	add_back_token(&(last_inst->cmd), new);
}
