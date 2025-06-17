/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:20:41 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 14:55:54 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '-' && str[i] != '+' && !ft_isdigit(str[i]))
		return (1);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_clean_exit(t_data *dt, char **tmp, int status)
{
	ft_free_double(tmp);
	free(dt->input);
	if (dt->env)
		ft_free_env(dt->env);
	exit (status);
}

void	ft_handle_exit_args(t_data *dt, char **tmp)
{
	if (!tmp[1])
	{
		ft_putendl_fd("exit", 1);
		ft_clean_exit(dt, tmp, 0);
	}
	else if (check_is_numeric(tmp[1]) == 1)
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		ft_clean_exit(dt, tmp, -1);
	}
	else if (tmp[2])
	{
		ft_free_double(tmp);
		free(dt->input);
		dt->exitstatus = 1;
		ft_putendl_fd("exit: too many arguments", 2);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		ft_clean_exit(dt, tmp, ft_atoi(tmp[1]));
	}
}

void	ft_builtin_exit(t_data *dt)
{
	char	**tmp;

	if (!dt->input)
		ctld_handler(dt);
	tmp = ft_split(dt->input, ' ');
	if (!tmp)
	{
		free(dt->input);
		ft_free_env(dt->env);
		exit (1);
	}
	ft_handle_exit_args(dt, tmp);
}
