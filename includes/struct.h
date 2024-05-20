/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:12:23 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/20 15:02:47 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_bash
{
	char					*working_directory;
	char					*sequence;
	int						exit_code;
	struct s_env			*env;
	struct s_instruction	*instruction;
}							t_bash;

typedef struct s_env
{
	char					*name;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_instruction
{
	struct s_token			*red;
	struct s_token			*cmd;
	int						fd[2];
	char					**cmd_array;
	struct s_instruction	*next;
}							t_instruction;

typedef struct s_token
{
	char					*data;
	int						data_type;
	int						n_quotes;
	char					*option;
	int						option_type;
	struct s_token			*next;
}							t_token;

// struct_utils/init.c

void			init_bash(t_bash **bash, char **envp);
t_env			*init_env(t_bash *bash, char **envp);
t_instruction	*init_instruction(t_bash *bash);
t_token			*init_token(t_bash *bash);

// struct_utils/new.c

t_env			*new_env(char *name_to_value);
t_instruction	*new_instruction(void);
t_token			*new_token(void);

// struct_utils/add_back.c

void			add_back_env(t_env **env, t_env *new);
void			add_back_instruction(t_instruction **inst, t_instruction *new);
void			add_back_token(t_token **token, t_token *new);

// struct_utils/last.c

t_env			*last_env(t_env *env);
t_instruction	*last_instruction(t_instruction *inst);
t_token			*last_token(t_token *token);

// struct_utils/clear_all.c

void			*clear_bash_and_exit(t_bash **bash, int exit_code);
void			*clear_bash(t_bash **bash);
void			*clear_env(t_env **env);
void			*clear_instruction(t_instruction **instruction);
void			*clear_token(t_token **token);

// struct_utils/clear_one.c

#endif
