/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:43:18 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/05 17:05:22 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_read_history(char *file)
{
	char	*line;
	int		fd;
	int		len;

	fd = open(file, O_RDWR | O_CREAT, 0777);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		add_history(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	ft_init_data(t_data *dt, int arc, char **env)
{
	if (arc != 1)
	{
		ft_putendl_fd("Usage: ./minishell", 2);
		exit(EXIT_FAILURE);
	}
	print_banner();
	if (ft_save_env(dt, env))
		return (1);
	if (ft_read_history(HISTORY_FILE))
		return (1);
	dt->cwd = getcwd(NULL, 0);
	if (!dt->cwd)
		return (1);
	dt->exitstatus = 0;
	return (dt->exitstatus);
}
