/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_commands_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:48:49 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/04 15:35:51 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin_child(t_cmd *cur_cmd, t_data *dt)
{
	dt->exitstatus = ft_execute_builtin(cur_cmd, dt);
	exit(dt->exitstatus);
}

int	save_stdio(int *saved_stdout, int *saved_stdin)
{
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
		return (1);
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin == -1)
	{
		close(*saved_stdout);
		return (1);
	}
	return (0);
}

int	exec_builtin_parent(t_cmd *cur_cmd, t_data *dt, pid_t *pids)
{
	int	saved_stdout;
	int	saved_stdin;

	if (save_stdio(&saved_stdout, &saved_stdin))
		return (free(pids), perror("dup"), 1);
	if (ft_handle_redirct(cur_cmd->redirect))
	{
		close(saved_stdout);
		close(saved_stdin);
		free(pids);
		return (dt->exitstatus = 1);
	}
	dt->exitstatus = ft_execute_builtin(cur_cmd, dt);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	return (0);
}

void	exec_external_cmd(t_cmd *cur_cmd, t_data *dt,
							int *pipe_fd, int has_pipe)
{
	char	*path;
	char	**tmp_env;

	path = ft_get_path(cur_cmd->args[0], dt);
	if (path)
	{
		tmp_env = ft_create_tmp_env(dt->env);
		execve(path, cur_cmd->args, tmp_env);
		perror("execve failed");
		exit(1);
	}
	else
	{
		if (has_pipe)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		ft_putstr_fd(cur_cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}

void	setup_child_pipes(int prev_fd, int *pipe_fd,
							int has_pipe, t_redirect *redirect)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (has_pipe && !redirects_to_stdout(redirect))
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe to stdout");
			exit(1);
		}
	}
	if (has_pipe)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}
