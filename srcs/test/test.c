/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:54:57 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/18 15:33:27 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	test_print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	test_print_instruction(t_instruction *instruction)
{
	t_instruction	*tmp;
	int				i;

	i = 1;
	tmp = instruction;
	while (tmp)
	{
		ft_printf("\n- INST : %d -------------------\n", i);
		test_print_red_token(tmp->red);
		test_print_cmd_token(tmp->cmd);
		i++;
		tmp = tmp->next;
	}
}

void	test_print_cmd_token(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = token;
	ft_printf("\n----------- CMD TOKEN --------\n\n");
	while (tmp)
	{
		ft_printf("TOKEN : %-4d", i);
		ft_printf("DATA : %-20s", tmp->data);
		ft_printf("N_QUOTES : %-2d", tmp->n_quotes);
		ft_printf("TYPE : %-4d\n", tmp->data_type);
		i++;
		tmp = tmp->next;
	}
}

void	test_print_red_token(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = token;
	ft_printf("\n----------- RED TOKEN --------\n\n");
	while (tmp)
	{
		ft_printf("TOKEN : %-4d", i);
		ft_printf("DATA : %-20s", tmp->data);
		ft_printf("OPTION : %-20s", tmp->option);
		ft_printf("N_QUOTES : %-8d", tmp->n_quotes);
		ft_printf("DATA_TYPE : %-8d", tmp->data_type);
		ft_printf("OPTION_TYPE : %-8d\n", tmp->option_type);
		i++;
		tmp = tmp->next;
	}
}
