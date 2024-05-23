/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:48:16 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/23 15:19:03 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// MINISHELL HEADER

# include "minishell.h"

// parser/parser.c

int		check_instruction(t_instruction *instruction);
void	update_instruction(t_bash *bash, t_instruction *instruction);

// parser/parser_check_redirections.c

int		check_redirections(t_token *red);
int		check_data_redirection(char *data, int type);
int		check_opt_redirection(char *option, int type);
int		unexpected_red_token(char c);

// parser/parser_check_cmd.c

int		check_cmd(t_token *cmd);
int		check_data_cmd(char *data, int type);
int		unexpected_cmd_token(char c);

// parser/parser_check_utils.c

int		type_equal_to(int flag, int type);
int		check_closed_quotes(char *data);
int		check_text_out_of_quotes(char *data, int (*is_unexpected_token)(char));
int		print_parsing_error_msg(char *msg, char *token_str, char token_c);

// parser/parser_update_data.c

char	*update_data(t_bash *bash, char *data);
void	filter_data(t_bash *bash, t_list **recast, char *src, char quote);
void	get_text_unchanged(t_bash *bash, t_list **recast, char *src, int *i);
void	get_text_in_quotes(t_bash *bash, t_list **recast, char *data, int *i);

// parser/parser_update_data_utils.c

void	free_content(void *content);
void	add_back_recast(t_bash *bash, t_list **recast, char *value);
int		count_length_data_updated(t_list *recast);
char	*duplicate_data_updated(t_bash *bash, t_list *recast, int size);
void	fill_cmd_array(t_bash *bash, t_instruction *instruction);

// parser/parser_update_expansion.c

void	get_dollar_sign(t_bash *bash, t_list **recast, int *i);
void	get_last_cmd_exit_status(t_bash *bash, t_list **recast, int *i);
void	get_process_id(t_bash *bash, t_list **recast, int *i);
void	get_minishell_name(t_bash *bash, t_list **recast, int *i);
void	get_env_value(t_bash *bash, t_list **recast, char *data, int *i);

#endif
