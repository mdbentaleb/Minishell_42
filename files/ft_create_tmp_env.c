/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tmp_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:24:18 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 14:56:25 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lst_size(t_env *lst)
{
	t_env	*cur;
	int		i;

	cur = lst;
	i = 0;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

char	**ft_create_tmp_env(t_env *env)
{
	t_env	*cur;
	char	**arr;
	char	*tmp_str;
	int		i;

	i = lst_size(env);
	arr = malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);
	i = 0;
	cur = env;
	while (cur)
	{
		tmp_str = ft_strjoin(cur->key, "=");
		if (cur->value)
		{
			arr[i++] = ft_strjoin(tmp_str, cur->value);
			free(tmp_str);
		}
		else
			arr[i++] = tmp_str;
		cur = cur->next;
	}
	arr[i] = NULL;
	return (arr);
}
