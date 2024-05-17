/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:12:23 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/17 18:18:11 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_bash
{
	char					*working_directory;
	int						exit_code;
	struct s_env			*env;
	struct s_instruction	*instruction;
}							t_bash;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_instruction
{
	struct s_token_red		*red;
	struct s_token_cmd		*cmd;
	int						fd[2];
	char					**cmd_array;
	struct s_instruction	*next;
}							t_instruction;

typedef struct s_token
{
	char				*data;
	int					type;
	char				*option;
	struct s_token	*next;
}						t_token;

// struct_utils/init.c

void			init_bash(t_bash **bash, char **envp);
t_env			*init_env(t_bash *bash, char **envp);

// struct_utils/new.c

t_env			*new_env(char *name_to_value);
t_instruction	*new_instruction(void);

// struct_utils/add_back.c

void			add_back_env(t_env **env, t_env *new);

// struct_utils/last.c

t_env			*last_env(t_env *env);

// struct_utils/clear_all.c

void			*clear_bash_and_exit(t_bash **bash, int exit_code);
void			*clear_bash(t_bash **bash);
void			*clear_env(t_env **env);
void			*clear_instruction(t_instruction **instruction);

// struct_utils/clear_one.c

#endif
