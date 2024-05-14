/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ben.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebrandt <bebrandt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:18:33 by bebrandt          #+#    #+#             */
/*   Updated: 2024/05/14 17:30:51 by bebrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(void)
{
	t_instructions	inst;

	inst.fd[0] = 1;
	inst.fd[1] = 2;
	ft_printf("main function for ben\n");
	prompt();
	ft_printf("\n");
	ft_printf("fd[0] = %d\n", inst.fd[0]);
	ft_printf("fd[0] = %d\n", inst.fd[1]);
}
