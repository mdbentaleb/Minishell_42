/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:30:11 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/04 17:32:25 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_var = 0;

void	ft_change_global(int flag)
{
	g_var = flag;
}

void	ctld_handler(t_data *dt)
{
	ft_free_env(dt->env);
	if (!dt->input)
	{
		printf("\033[1A");
		printf("\033[12C");
		printf("exit\n");
	}
	exit(0);
}

void	ctlc_handler(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_var == 0)
		rl_redisplay();
}

void	ft_signals(void)
{
	signal(SIGINT, ctlc_handler);
	signal(SIGQUIT, SIG_IGN);
}
