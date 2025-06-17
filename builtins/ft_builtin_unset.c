/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:11:39 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 14:56:03 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_need_del(t_data *dt, char *arg)
{
	t_env	*cur;
	t_env	*tmp;

	cur = dt->env;
	tmp = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, arg) == 0)
		{
			if (tmp == NULL)
				dt->env = cur->next;
			else
				tmp->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		tmp = cur;
		cur = cur->next;
	}
}

int	ft_builtin_unset(char **args, t_data *dt)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valide_arg(args[i], 0) == 0)
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			dt->exitstatus = 1;
		}
		else
		{
			is_need_del(dt, args[i]);
			dt->exitstatus = 0;
		}
		i++;
	}
	return (dt->exitstatus);
}
