/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_redirct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:06:18 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 11:36:06 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_handle_out(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open >"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("handle redirect out dup2"), close(fd), 1);
	close(fd);
	return (0);
}

static int	ft_handle_append(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (perror("handle redirect >> open file"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("handle redirect append dup2"), close(fd), 1);
	close(fd);
	return (0);
}

static int	ft_handle_in_hrdc(char *file, int is_hrdoc)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (is_hrdoc)
			perror("open heredoc");
		else
			perror("open <");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("handle herdoc dup2"), close(fd), 1);
	close(fd);
	return (0);
}

int	ft_handle_redirct(t_redirect *redir)
{
	while (redir)
	{
		if (redir->type == RED_OUT)
		{
			if (ft_handle_out(redir->file))
				return (1);
		}
		else if (redir->type == RED_APPEND)
		{
			if (ft_handle_append(redir->file))
				return (1);
		}
		else if (redir->type == RED_IN || redir->type == RED_HEREDOC)
			if (ft_handle_in_hrdc(redir->file, redir->type == RED_HEREDOC))
				return (1);
		redir = redir->next;
	}
	return (0);
}
