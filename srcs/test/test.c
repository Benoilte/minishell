/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <benoit.brandt@proton.me>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:54:57 by bebrandt          #+#    #+#             */
/*   Updated: 2024/06/19 12:28:48 by bebrandt         ###   ########.fr       */
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
		ft_printf("\n inst->prev = %p ---- inst = %p\n\n", tmp->prev, tmp);
		test_print_cmd_array(tmp->cmd_array);
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
	ft_printf("\033[0;36m");
	ft_printf("\n----------- CMD TOKEN --------\n\n");
	while (tmp)
	{
		ft_printf("TOKEN : %-4d", i);
		ft_printf("DATA : %-30s", tmp->data);
		ft_printf("TYPE : %-8d\n", tmp->data_type);
		i++;
		tmp = tmp->next;
	}
	ft_printf("\033[0m");
}

void	test_print_red_token(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = token;
	ft_printf("\033[0;32m");
	ft_printf("\n----------- RED TOKEN --------\n\n");
	while (tmp)
	{
		ft_printf("TOKEN : %-4d", i);
		ft_printf("DATA : %-10s", tmp->data);
		ft_printf("OPTION : %-30s", tmp->option);
		ft_printf("DATA_TYPE : %-8d", tmp->data_type);
		ft_printf("OPTION_TYPE : %-8d\n", tmp->option_type);
		i++;
		tmp = tmp->next;
	}
	ft_printf("\033[0m");
}

void	test_print_cmd_array(char **cmd_array)
{
	int	i;

	i = 0;
	ft_printf("\033[0;33m");
	ft_printf("----------- cmd array --------\n\n");
	while (cmd_array[i])
	{
		if (cmd_array[i + 1])
			ft_printf("%s, ", cmd_array[i]);
		else
			ft_printf("%s\n", cmd_array[i]);
		i++;
	}
	ft_printf("\033[0m");
}
