/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:54:57 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/18 11:49:46 by bebrandt         ###   ########.fr       */
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

void	test_print_cmd_token(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 1;
	tmp = token;
	while (tmp)
	{
		ft_printf("TOKEN : %d   ", i);
		ft_printf("DATA : %s   ", tmp->data);
		ft_printf("N_QUOTES : %d   ", tmp->n_quotes);
		ft_printf("TYPE : %d\n", tmp->data_type);
		i++;
		tmp = tmp->next;
	}
}
