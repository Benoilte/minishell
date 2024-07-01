/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:38:16 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/30 22:07:01 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2024/06/25 22:32:09 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "exec.h"

enum
{
	FT_ENV_WITHOUT_CMD,
	FT_ENV_WITH_CMD
};

// builtins/ft_exit.c

void	ft_exit(t_instruction *instruction, t_bash *bash);

// builtins/pwd.c

void	pwd(t_instruction *instruction);

// builtins/cd.c

void	cd(t_instruction *instruction, t_env **env);
void	cd_go_home(t_instruction *instruction, t_env **env, char *oldpwd);
void	cd_move_dir(t_instruction *inst, char *dir, t_env **env, char *oldcwd);
void	set_cwd_env(t_instruction *inst, t_env **env, char *name, char *value);
void	ft_chdir_error(char *directory, int fd);

// builtins/env.c

int		ft_env(t_bash *bash, t_instruction *instruction);
int		print_env(char **ms_env);
int		env_has_cmd(t_instruction *instruction);
int		exec_env_with_cmd(t_bash *bash, t_instruction *instruction);
int		exec_env_without_cmd(char **ms_env, t_instruction *instruction);

// builtins/ft_env.c

void	add_arg_env(t_bash *bash, t_token *current_arg);

//builtins/echo.c

void	echo(t_instruction *instruciton);

//builtins/export.c

void	ft_export(t_env *env, t_instruction *instruction);
int		set_env_var_liste(t_env *env, char *envp);

//builtins/unset.c

void	ft_unset(t_env **env, t_instruction *instruction);

//builtins/utils_builtins.c

int		ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);

#endif
