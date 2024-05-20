/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:41:41 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/20 11:53:12 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	set_redirection(t_bash *bash, char *sequence, int *i)
{
	t_token			*new;
	t_instruction	*last_inst;

	new = new_token();
	if (!new)
		clear_bash_and_exit(&bash, EXIT_FAILURE);
	define_red_token_type(new, sequence, i);
	new->data = get_redirection_data(bash, new, i);
	while (ft_isspace(sequence[*i]))
		*i += 1;
	if (sequence[*i])
		set_token_option(bash, new, sequence, i);
	last_inst = last_instruction(bash->instruction);
	add_back_token(&(last_inst->red), new);
}

void	set_token_option(t_bash *bash, t_token *new, char *sequence, int *i)
{
	if ((sequence[*i] == '<') || (sequence[*i] == '>'))
		new->option = get_redirection_data(bash, new, i);
	else
		new->option = get_text_data(bash, new, &(new->option_type), i);
	new->option_type |= REDIRECTION;
}
