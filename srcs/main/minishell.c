/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:29:53 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/14 13:04:04 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	ft_printf("main function for minishell\n");
	ft_printf("\n");
	prompt();
	ft_printf("\n");
	lexer();
	ft_printf("\n");
	parser();
	ft_printf("\n");
	builtins();
	ft_printf("\n");
	exec();
	ft_printf("\n");
	test();
}
