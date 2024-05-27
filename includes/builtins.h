/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:38:16 by tmartin2          #+#    #+#             */
/*   Updated: 2024/05/27 13:13:57 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
 
// builtins/pwd.c

void pwd(t_instruction *instruction);

// builtins/cd.c

void cd(t_instruction *instruction);

//builtins/exit.c

int ft_exit(t_instruction *instruction);
void trim(t_instruction *instruction);

//builtins/env.c

void print_env(t_env *env);

//builtins/echo.c

void echo(t_instruction *instruciton);

//builtins/export.c

void ft_export(t_env *env, t_instruction *instruction);
int set_env_var_liste(t_env *env, char *envp);

//builtins/unset.c

void ft_unset(t_env **env, t_instruction *instruction);

//builtins/utils_builtins.c

int	ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
#endif