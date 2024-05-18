/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:41:41 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/18 15:06:05 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_input_redirection(t_bash *bash, char *sequence, int *i)
{
	int				origin;
	t_token			*new;
	t_instruction	*last_inst;

	new = new_token();
	if (!new)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	origin = *i;
	define_red_token_type(new, sequence, i);
	new->data = ft_substr(sequence, origin, *i - origin);
	if (!new->data)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	while (ft_isspace(sequence[*i]))
		*i += 1;
	set_token_option(bash, new, sequence, i);
	last_inst = last_instruction(bash->instruction);
	add_back_token(&(last_inst->red), new);
}

void	set_output_redirection(t_bash *bash, char *sequence, int *i)
{
	int				origin;
	t_token			*new;
	t_instruction	*last_inst;

	new = new_token();
	if (!new)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	origin = *i;
	define_red_token_type(new, sequence, i);
	new->data = ft_substr(sequence, origin, *i - origin);
	if (!new->data)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	while (ft_isspace(sequence[*i]))
		*i += 1;
	set_token_option(bash, new, sequence, i);
	last_inst = last_instruction(bash->instruction);
	add_back_token(&(last_inst->red), new);
}

void	set_token_option(t_bash *bash, t_token *new, char *sequence, int *i)
{
	if ((sequence[*i] == '\"') || (sequence[*i] == '\''))
	{
		define_quotes_token_type(&(new->option_type), sequence[*i]);
		new->option = get_data_in_quotes(bash, new, sequence, i);
	}
	else
		new->option = get_word(bash, new, sequence, i);
	new->option_type |= REDIRECTION;
}
