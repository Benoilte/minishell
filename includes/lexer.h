/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:58:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/20 13:57:58 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// MINISHELL HEADER

# include "minishell.h"

//lexer/lexer.c

// void	set_quotes(t_bash *bash, char *sequence, int *i, int *cmd);
void	set_pipe(t_bash *bash, int *i, int *cmd);
void	set_text_token(t_bash *bash, char *sequence, int *i, int *cmd);

//lexer/lexer_cmd.c

int		is_builtin(char *word);

//lexer/lexer_redirections.c

void	set_redirection(t_bash *bash, char *sequence, int *i);
void	set_token_option(t_bash *bash, t_token *new, char *sequence, int *i);

//lexer/lexer_get_str.c

// char	*get_data_in_quotes(t_bash *bash, t_token *new, char *sequence, int *i);
char	*get_text_data(t_bash *bash, t_token *new, int *type, int *i);
void	move_to_next_quote(char quote, char *sequence, int *i);
char	*get_redirection_data(t_bash *bash, t_token *new, int *i);
char	*get_one_char_token(t_bash *bash, t_token *new, char *sequence, int *i);
char	*get_substr_or_exit(t_bash *bash, t_token *new, int start, int i);

//lexer/lexer_define_type.c

void	define_cmd_token_type(t_token *token, int *cmd);
void	define_quotes_token_type(int *type, char quote);
void	define_red_token_type(t_token *new, char *sequence, int *i);

#endif
