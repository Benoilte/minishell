/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:58:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/07/18 08:34:09 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// MINISHELL HEADER

# include "minishell.h"

//lexer/lexer.c

int		set_pipe(t_bash *bash, int *i, int *cmd);
int		set_text_token(t_bash *bash, char *sequence, int *i, int *cmd);
int		set_redirection(t_bash *bash, char *sequence, int *i);
int		set_token_option(t_token *new, char *sequence, int *i);

//lexer/lexer_action_utils.c

void	move_to_next_quote(char *sequence, int *i);

//lexer/lexer_get_data.c

char	*get_text_data(char *sequence, int *i, int *type);
char	*get_redirection_data(char *sequence, int *i);

//lexer/lexer_define_type.c

void	define_cmd_token_type(t_token *token, int *cmd);
void	define_quotes_token_type(int *type, char quote);
void	define_red_token_type(t_token *new, char *sequence, int *i);

#endif
