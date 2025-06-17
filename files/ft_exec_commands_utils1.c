/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_commands_utils1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:40:38 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 11:31:51 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin_no_pipe(t_cmd *cur_cmd, int has_pipe)
{
	if (cur_cmd->args && cur_cmd->args[0]
		&& ft_is_builtin(cur_cmd->args) && !has_pipe)
		return (1);
	return (0);
}

void	handle_child_process(t_cmd *cur_cmd, t_data *dt,
								int prev_fd, int *pipe_fd)
{
	int	has_pipe;

	has_pipe = (cur_cmd->next != NULL);
	setup_child_pipes(prev_fd, pipe_fd, has_pipe, cur_cmd->redirect);
	if (ft_handle_redirct(cur_cmd->redirect))
		exit(1);
	if (cur_cmd->args && cur_cmd->args[0] && ft_is_builtin(cur_cmd->args))
		exec_builtin_child(cur_cmd, dt);
	exec_external_cmd(cur_cmd, dt, pipe_fd, has_pipe);
}

void	handle_parent_process(int *pipe_fd, int *prev_fd,
								int has_pipe)
{
	if (has_pipe)
	{
		close(pipe_fd[1]);
		if (*prev_fd != -1)
			close(*prev_fd);
		*prev_fd = pipe_fd[0];
	}
	else
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
	}
}

void	cleanup_fork_error(int *pipe_fd, int *prev_fd, int has_pipe, t_data *dt)
{
	int	j;

	if (has_pipe)
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
	}
	if (*prev_fd != -1)
		close(*prev_fd);
	j = 0;
	while (j < dt->cmd_index)
	{
		waitpid(dt->pids[j], NULL, 0);
		j++;
	}
	free(dt->pids);
}

int	fork_and_exec(t_cmd *cur_cmd, t_data *dt, int *pipe_fd, int *prev_fd)
{
	int	has_pipe;
	int	*i_ptr;

	has_pipe = (cur_cmd->next != NULL);
	i_ptr = &dt->cmd_index;
	dt->pid = fork();
	if (dt->pid == -1)
	{
		perror("fork: ");
		cleanup_fork_error(pipe_fd, prev_fd, has_pipe, dt);
		return (1);
	}
	dt->pids[(*i_ptr)++] = dt->pid;
	if (dt->pid == 0)
		handle_child_process(cur_cmd, dt, *prev_fd, pipe_fd);
	else
		handle_parent_process(pipe_fd, prev_fd, has_pipe);
	return (0);
}
