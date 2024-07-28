/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:46:20 by hchadili          #+#    #+#             */
/*   Updated: 2024/07/28 16:26:48 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void sigusr_handler(int sig)
{
	(void)sig;
	if(sig == SIGQUIT)
	{
		ft_exit_status(127, SET);
		return;
	}
	else
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		ft_exit_status(130, SET);
	}
}

void ft_signal(void)
{
	signal(SIGINT, sigusr_handler);
	signal(SIGQUIT, sigusr_handler);
}