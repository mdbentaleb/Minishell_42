/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:42:54 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 11:09:18 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = ft_strdup(value);
			return ;
		}
		cur = cur->next;
	}
	ft_add_env(env, ft_strdup(key), ft_strdup(value));
}

static char	*ft_get_target_path(t_cmd *cmd, t_data *dt)
{
	char	*path;

	path = NULL;
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
	{
		path = ft_expand_vars(dt, "HOME");
		if (!path)
			ft_putendl_fd("cd: HOME not set", 2);
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		path = ft_expand_vars(dt, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			return (NULL);
		}
		else
			printf("%s\n", path);
	}
	else
		path = cmd->args[1];
	return (path);
}

static int	ft_change_dir(t_data *dt, char *path, char *oldpwd)
{
	char	*newpwd;

	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		dt->exitstatus = 1;
		return (dt->exitstatus);
	}
	newpwd = getcwd(NULL, 0);
	if (newpwd)
	{
		update_env_var(&dt->env, "OLDPWD", oldpwd);
		update_env_var(&dt->env, "PWD", newpwd);
		free(newpwd);
	}
	else
		perror ("cd");
	free(oldpwd);
	dt->exitstatus = 0;
	return (dt->exitstatus);
}

int	ft_builtin_cd(t_cmd *cmd, t_data *dt)
{
	char	*path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("cd");
		dt->exitstatus = 1;
		return (dt->exitstatus);
	}
	path = ft_get_target_path(cmd, dt);
	if (!path)
	{
		free (oldpwd);
		return (dt->exitstatus = 1);
	}
	return (ft_change_dir(dt, path, oldpwd));
}
