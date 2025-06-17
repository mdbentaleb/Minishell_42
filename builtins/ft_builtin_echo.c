/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:04:28 by ouzouini          #+#    #+#             */
/*   Updated: 2025/06/05 13:11:14 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_builtin_echo(t_cmd *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	while (cmd->args[i] && strncmp(cmd->args[i], "-n", 2) == 0 
		&& check_n(cmd->args[i]) == 0)
	{
		new_line = 1;
		i++;
	}
	while (cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == 0)
		write(1, "\n", 1);
	return (0);
}
