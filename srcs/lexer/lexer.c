/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:53:37 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/17 21:51:17 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	lexing(t_bash *bash, char *sequence)
{
	int	i;
	int	cmd;
	int	return_status;

	i = 0;
	cmd = 0;
	return_status = RETURN_SUCCESS;
	bash->instruction = init_instruction();
	if (!bash->instruction)
		return (RETURN_FAILURE);
	while ((return_status == RETURN_SUCCESS) && sequence[i])
	{
		if (ft_isspace(sequence[i]))
			i++;
		else if ((sequence[i] == '<') || (sequence[i] == '>'))
			return_status = set_redirection(bash, sequence, &i);
		else if (sequence[i] == '|')
			return_status = set_pipe(bash, &i, &cmd);
		else
			return_status = set_text_token(bash, sequence, &i, &cmd);
	}
	return (return_status);
}

int	set_pipe(t_bash *bash, int *i, int *cmd)
{
	t_instruction	*new;

	new = init_instruction();
	if (!new)
		return (RETURN_FAILURE);
	add_back_instruction(&(bash->instruction), new);
	*cmd = 0;
	*i += 1;
	return (RETURN_SUCCESS);
}

int	set_text_token(t_bash *bash, char *sequence, int *i, int *cmd)
{
	t_token			*new;
	t_instruction	*last_inst;

	new = init_token();
	if (!new)
		return (RETURN_FAILURE);
	new->data = get_text_data(sequence, i, &(new->data_type));
	if (!new->data)
	{
		clear_token(&new);
		return (RETURN_FAILURE);
	}
	define_cmd_token_type(new, cmd);
	last_inst = last_instruction(bash->instruction);
	add_back_token(&(last_inst->cmd), new);
	return (RETURN_SUCCESS);
}

int	set_redirection(t_bash *bash, char *sequence, int *i)
{
	t_token			*new;
	t_instruction	*last_inst;

	new = init_token();
	if (!new)
		return (RETURN_FAILURE);
	define_red_token_type(new, sequence, i);
	new->data = get_redirection_data(sequence, i);
	if (!new->data)
	{
		clear_token(&new);
		return (RETURN_FAILURE);
	}
	while (ft_isspace(sequence[*i]))
		*i += 1;
	if (set_token_option(new, sequence, i) == RETURN_FAILURE)
	{
		clear_token(&new);
		return (RETURN_FAILURE);
	}
	last_inst = last_instruction(bash->instruction);
	add_back_token(&(last_inst->red), new);
	return (RETURN_SUCCESS);
}

int	set_token_option(t_token *new, char *sequence, int *i)
{
	if (sequence[*i] == '\0')
		return (RETURN_SUCCESS);
	if ((sequence[*i] == '<') || (sequence[*i] == '>'))
	{
		new->option = get_redirection_data(sequence, i);
		if (!new->option)
			return (RETURN_FAILURE);
	}
	else
	{
		new->option = get_text_data(sequence, i, &(new->option_type));
		if (!new->option)
			return (RETURN_FAILURE);
		if (ft_strlen(new->option) == 0)
		{
			free(new->option);
			new->option = NULL;
		}
	}
	new->option_type |= REDIRECTION;
	return (RETURN_SUCCESS);
}
