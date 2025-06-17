/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:11:19 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/04 22:34:48 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_write_heredoc_loop(int fd, char *delimiter, t_data *dt)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		tmp = expand_heredoc_preserve_quotes(line, dt);
		if (tmp)
		{
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 1);
			free(tmp);
		}
		else
			return (free(line), 1);
		free(line);
	}
	return (0);
}

static void	ft_heredoc_child_process(char *filename,
										char *delimiter, t_data *dt)
{
	int	fd;

	signal(SIGINT, SIG_DFL);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc open");
		exit(1);
	}
	if (ft_write_heredoc_loop(fd, delimiter, dt))
		free(filename);
	close(fd);
	exit(0);
}

static int	ft_heredoc_parent_process(int pid, char *filename, t_data *dt)
{
	waitpid(pid, &dt->exitstatus, 0);
	signal(SIGINT, ctlc_handler);
	if (WIFSIGNALED(dt->exitstatus) && WTERMSIG(dt->exitstatus) == SIGINT)
	{
		free(filename);
		return (0);
	}
	return (1);
}

static char	*ft_create_get_herdoc_content(char *delimiter, t_data *dt)
{
	char	*filename;
	int		pid;

	ft_change_global(1);
	filename = ft_strdup("/tmp/.heredoc_tmp.txt");
	if (!filename)
		return (perror("Herdoc file name"), NULL);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (free(filename), NULL);
	}
	if (pid == 0)
		ft_heredoc_child_process(filename, delimiter, dt);
	if (!ft_heredoc_parent_process(pid, filename, dt))
		return (NULL);
	return (filename);
}

int	ft_prepare_heredocs(t_cmd *cmd, t_data *dt)
{
	t_cmd		*cur;
	t_redirect	*redir;
	char		*tmpfile;

	cur = cmd;
	while (cur)
	{
		redir = cur->redirect;
		while (redir)
		{
			if (redir->type == RED_HEREDOC)
			{
				tmpfile = ft_create_get_herdoc_content(redir->file, dt);
				ft_change_global(0);
				if (!tmpfile)
					return (1);
				free(redir->file);
				redir->file = tmpfile;
			}
			redir = redir->next;
		}
		cur = cur->next;
	}
	return (0);
}
