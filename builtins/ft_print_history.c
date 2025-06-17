/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:30:09 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 14:56:05 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_print_history(t_cmd *cmd, char *file)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	i = 1;
	if (cmd->args[1] != NULL)
	{
		ft_putendl_fd("history: too many arguments", 2);
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (i < 10)
			printf("    [%d]   %s", i, line);
		else if (i >= 10)
			printf("    [%d]  %s", i, line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (close(fd), 0);
}
