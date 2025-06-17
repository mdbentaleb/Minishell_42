/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:15:49 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 11:09:25 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_print_export(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (cur->key && cur->value)
			printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		else if (cur->key && cur->value == NULL)
			printf("declare -x %s\n", cur->key);
		cur = cur->next;
	}
	return (0);
}

static void	ft_hadle_key_value(char *arg, t_data *dt, int i)
{
	char	*key;
	char	*value;
	int		len;

	len = ft_strlen(arg);
	key = ft_substr(arg, 0, i);
	value = ft_substr(arg, i + 1, len - i - 1);
	is_need_del(dt, key);
	ft_add_env(&dt->env, key, value);
	free(key);
	free(value);
}

void	ft_add_export_kyvl(char *arg, t_data *dt)
{
	int		i;

	i = 0;
	if (!check_export_arg(arg))
	{
		is_need_del(dt, arg);
		ft_add_env(&dt->env, arg, NULL);
	}
	else
	{
		while (arg[i])
		{
			if (arg[i] == '=')
			{
				ft_hadle_key_value(arg, dt, i);
				break ;
			}
			i++;
		}
	}
}

int	ft_builtin_export(t_cmd *cmd, t_data *dt)
{
	int	i;

	i = 1;
	if (cmd->args[1] == NULL)
		return (ft_print_export(dt->env));
	else
	{
		while (cmd->args[i])
		{
			if (is_valide_arg(cmd->args[i], 1) == 0)
			{
				ft_putstr_fd("export: ", 2);
				ft_putstr_fd(cmd->args[i], 2);
				ft_putendl_fd(": not a valid identifier", 2);
				dt->exitstatus = 1;
			}
			else
			{
				ft_add_export_kyvl(cmd->args[i], dt);
				dt->exitstatus = 0;
			}
			i++;
		}
	}
	return (dt->exitstatus);
}
