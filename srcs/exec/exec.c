/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmartin2 <tmartin2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:53:54 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/21 15:36:08 by tmartin2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/exec.h"

// //fonction teste qui recupere les instruction 
// // Fonction pour ajouter une instruction à la liste chaînée
// void add_instruction(t_bash *bash, t_instruction *new_instr)
// {
//     if (!bash->instruction)
//     {
//         bash->instruction = new_instr;
//     }
//     else
//     {
//         t_instruction *current = bash->instruction;
//         while (current->next)
//         {
//             current = current->next;
//         }
//         current->next = new_instr;
//     }
// }
// void instruc(t_bash *bash)
// {
//     char **tokens;
//     t_instruction *new_instr;
//     int i;

//     // Diviser la séquence en tokens
//     tokens = ft_split(bash->sequence, ' ');
//     if (!tokens)
//         return;

//     // Initialiser une nouvelle instruction
//     new_instr = (t_instruction *)malloc(sizeof(t_instruction));
//     if (!new_instr)
//         return;

//     new_instr->cmd_array = tokens;
//     new_instr->next = NULL;

//     // Ajouter la nouvelle instruction à la liste chaînée
//     add_instruction(bash, new_instr);
// }
void ft_cmd(t_bash *bash, char **envp)
{
	char *cmd_path;
	t_instruction *current;
	cmd_path = check_instruction(&current->cmd->data, envp);
	if (execve(cmd_path, current->cmd->data, envp) == -1);
		error();
}
void	exec(t_bash *bash, char **envp)
{
	ft_cmd(bash, envp);
}
