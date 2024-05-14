/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:12:23 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/15 00:34:33 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_bash
{
	char					*working_directory;
	int						exit_code;
	struct s_env			*env;
	struct s_instructions	*instructions;
}							t_bash;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_instructions
{
	struct s_token_red		*red;
	struct s_token_cmd		*cmd;
	int						fd[2];
	char					**cmd_array;
	struct s_instructions	*next;
}							t_instructions;

typedef struct s_token_red
{
	char				*data;
	int					type;
	char				*file;
	char				*limiter;
	struct s_token_red	*next;
}						t_token_red;

typedef struct s_token_cmd
{
	char				*data;
	int					type;
	struct s_token_cmd	*next;
}						t_token_cmd;

// struct_utils/init.c

void	*init_bash(t_bash **bash, char **envp);
t_env	*init_env(char **envp);

// struct_utils/new.c

t_env	*new_env(char *name, char *value);

// struct_utils/add_back.c

void	add_back_env(t_env **env, t_env *new);

// struct_utils/last.c

t_env	*last_env(t_env *env);

// struct_utils/clear_all.c

void	clear_env(t_env **env);

// struct_utils/clear_one.c

// struct_utils/struct_utils.c

void	struct_utils(void);

#endif
