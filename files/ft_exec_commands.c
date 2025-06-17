/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:29:46 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 16:27:23 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_cmd(t_cmd *cur_cmd, t_data *dt, int *pipe_fd, int *prev_fd)
{
	int	has_pipe;

	has_pipe = (cur_cmd->next != NULL);
	if (has_pipe && setup_pipe(pipe_fd, prev_fd, dt->cmd_index, dt->pids))
		return (1);
	if (is_builtin_no_pipe(cur_cmd, has_pipe))
		return (exec_builtin_parent(cur_cmd, dt, dt->pids));
	return (fork_and_exec(cur_cmd, dt, pipe_fd, prev_fd));
}

static void	wait_for_processes(pid_t *pids, int count, t_data *dt)
{
	int	j;

	j = 0;
	while (j < count)
	{
		waitpid(pids[j], &dt->exitstatus, 0);
		j++;
	}
}

static int	init_exec_data(t_cmd *cmd, t_data *dt)
{
	int	cmd_count;

	if (ft_prepare_heredocs(cmd, dt))
		return (1);
	cmd_count = count_cmds(cmd);
	dt->pids = malloc(sizeof(pid_t) * cmd_count);
	if (!dt->pids)
		return (1);
	dt->cmd_index = 0;
	return (0);
}

static void	init_vars_exec_cmd(int *pip0, int *pip1, int *prev_fd)
{
	*pip0 = -1;
	*pip1 = -1;
	*prev_fd = -1;
}

int	exec_command(t_cmd *cmd, t_data *dt)
{
	int		pipe_fd[2];
	t_cmd	*cur_cmd;

	init_vars_exec_cmd(&pipe_fd[0], &pipe_fd[1], &dt->prev_fd);
	ft_change_global(1);
	if (init_exec_data(cmd, dt))
		return (dt->exitstatus = 1);
	cur_cmd = cmd;
	while (cur_cmd)
	{
		if (process_cmd(cur_cmd, dt, pipe_fd, &dt->prev_fd))
			return (dt->exitstatus = 1);
		cur_cmd = cur_cmd->next;
	}
	if (dt->prev_fd != -1)
		close(dt->prev_fd);
	wait_for_processes(dt->pids, dt->cmd_index, dt);
	ft_cleanup_heredocs(cmd);
	ft_change_global(0);
	free(dt->pids);
	if (WIFEXITED(dt->exitstatus))
		dt->exitstatus = WEXITSTATUS(dt->exitstatus);
	else
		dt->exitstatus = 1;
	return (0);
}
