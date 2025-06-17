/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_commands_utils3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:55:16 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/05 13:13:02 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_builtin(char **arg)
{
	return ((!ft_strcmp(arg[0], "cd") || !ft_strcmp(arg[0], "echo")
			|| !ft_strcmp(arg[0], "pwd") || !ft_strcmp(arg[0], "export") 
			|| !ft_strcmp(arg[0], "unset")
			|| (!ft_strcmp(arg[0], "env") && arg[1] == NULL))
		|| !ft_strcmp(arg[0], "history"));
}

int	ft_execute_builtin(t_cmd *cmd, t_data *dt)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_builtin_cd(cmd, dt));
	else if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_builtin_echo(cmd));
	else if (!ft_strcmp(cmd->args[0], "env") && cmd->args[1] == NULL)
		return (ft_builtin_env(dt));
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_builtin_export(cmd, dt));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_builtin_unset(cmd->args, dt));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_builtin_pwd(cmd));
	else if (!ft_strcmp(cmd->args[0], "history"))
		return (ft_print_history(cmd, HISTORY_FILE));
	return (1);
}

int	count_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	cleanup_pids(pid_t *pids, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
	free(pids);
}

int	setup_pipe(int *pipe_fd, int *prev_fd, int i, pid_t *pids)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe: Too many open files");
		if (*prev_fd != -1)
		{
			close(*prev_fd);
			*prev_fd = -1;
		}
		cleanup_pids(pids, i);
		return (1);
	}
	return (0);
}
