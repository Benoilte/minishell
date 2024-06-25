/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:38:16 by tmartin2          #+#    #+#             */
/*   Updated: 2024/06/25 18:34:38 by bebrandt         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// builtins/pwd.c

void	pwd(t_instruction *instruction);

// builtins/cd.c

void	cd(t_instruction *instruction, t_env *env);
void	set_pwd(t_env *env, char *directory);

//builtins/env.c

void	print_env(t_env *env, t_instruction *instruction);

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