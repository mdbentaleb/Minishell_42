/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:09:05 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 15:07:54 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_add_env_node(t_data *dt, char *env_line)
{
	int		j;
	char	*key;
	char	*value;

	j = 0;
	while (env_line[j] && env_line[j] != '=')
		j++;
	if (env_line[j] == '=')
	{
		key = ft_substr(env_line, 0, j);
		if (!key)
			return (1);
		if (ft_strcmp(key, "OLDPWD") == 0)
			value = NULL;
		else
		{
			value = ft_substr(env_line, j + 1, ft_strlen(env_line) - j - 1);
			if (!value)
				return (free (key), 1);
		}
		ft_add_env(&dt->env, key, value);
		free(key);
		free(value);
	}
	return (0);
}

int	ft_save_env(t_data *dt, char **env)
{
	int		i;

	dt->env = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_add_env_node(dt, env[i]))
			return (1);
		i++;
	}
	return (0);
}
