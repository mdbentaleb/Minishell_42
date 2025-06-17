/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:30:08 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 16:31:18 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_write_history(char *file, char *line)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		return (perror("open file to write history"), 1);
	ft_putendl_fd(line, fd);
	close(fd);
	return (0);
}

void	ft_add_history(t_data *dt)
{
	if (ft_strlen(dt->input) > 0)
		add_history(dt->input);
	if (ft_write_history(HISTORY_FILE, dt->input))
		return ;
}
