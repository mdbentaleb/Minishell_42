/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:31:21 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/05 13:07:10 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	has_special_characters(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (ft_is_special_char(key[i]))
			return (1);
		i++;
	}
	return (0);
}

static char	**extract_key(char *key)
{
	char	**arr;

	if (has_special_characters(key))
	{
		arr = extract_key_utils(key);
		if (!arr)
			return (NULL);
	}
	else
	{
		arr = malloc(sizeof(char *) * 2);
		if (!arr)
			return (NULL);
		arr[0] = ft_strdup(key);
		if (!arr[0])
			return (ft_free_double(arr), NULL);
		arr[1] = NULL;
	}
	return (arr);
}

static char	*handle_value_merge(char **arrkey, char *tmp)
{
	char	*merge;

	if (arrkey[1] != NULL)
	{
		merge = ft_strjoin(tmp, arrkey[1]);
		if (!merge)
		{
			free(tmp);
			return (ft_free_double(arrkey), NULL);
		}
		free(tmp);
		ft_free_double(arrkey);
		return (merge);
	}
	ft_free_double(arrkey);
	return (tmp);
}

static char	*search_env_and_expand(t_env *cur, char **arrkey)
{
	char	*tmp;

	tmp = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, arrkey[0]) == 0)
		{
			if (cur->value)
			{
				tmp = ft_strdup(cur->value);
				if (!tmp)
					return (ft_free_double(arrkey), NULL);
			}
			return (handle_value_merge(arrkey, tmp));
		}
		cur = cur->next;
	}
	ft_free_double(arrkey);
	return (NULL);
}

char	*ft_expand_vars(t_data *dt, char *key)
{
	char	**arrkey;

	if (ft_strlen(key) == 1 && key[0] >= '0' && key[0] <= '9')
	{
		if (key[0] == '0')
			return (ft_strdup("zmbash"));
		else
			return (ft_strdup(""));
	}
	arrkey = extract_key(key);
	if (!arrkey)
		return (NULL);
	return (search_env_and_expand(dt->env, arrkey));
}
