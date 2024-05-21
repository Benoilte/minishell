/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:54:12 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/21 09:39:38 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

// TODO : structure bash en attande pour recupe le builtins
void builtins(t_bash *bash)
{
	int exit_status;
	exit_status = 0;
	pwd(bash);
	cd(bash);
	echo(bash);
	ft_export(bash->env, bash);
	ft_unset(bash);
	if (ft_strcmp(bash->sequence, "env") == 0)
		print_env(bash->env);
	exit_status = ft_exit(bash);
	if (exit_status != 0)
		exit(exit_status);
}
