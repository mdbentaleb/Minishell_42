/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_commands_utils4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:58:48 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 11:48:15 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cleanup_heredocs(t_cmd *cmd)
{
	t_cmd		*cur;
	t_redirect	*redir;

	cur = cmd;
	while (cur)
	{
		redir = cur->redirect;
		while (redir)
		{
			if (redir->type == RED_HEREDOC)
				unlink(redir->file);
			redir = redir->next;
		}
		cur = cur->next;
	}
}

int	redirects_to_stdout(t_redirect *redir)
{
	while (redir)
	{
		if (redir->type == RED_OUT || redir->type == RED_APPEND)
			return (1);
		redir = redir->next;
	}
	return (0);
}

static char	*ft_search_path(char **path_arr, char *cmd)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (path_arr && path_arr[i])
	{
		tmp = ft_strjoin(path_arr[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_double(path_arr);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (ft_free_double(path_arr), NULL);
}

static char	**get_path_arr(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
			return (ft_split(env->value, ':'));
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_path(char *cmd, t_data *dt)
{
	char	**path_arr;

	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0)
		return (ft_strdup(cmd));
	path_arr = get_path_arr(dt->env);
	return (ft_search_path(path_arr, cmd));
}
