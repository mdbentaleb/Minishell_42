/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_vars_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:40:08 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 11:09:46 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**cleanup_and_return_null(char *tmp1, char *tmp2, char **arr)
{
	free(tmp1);
	free(tmp2);
	return (ft_free_double(arr), NULL);
}

static int	split_key_on_special_char(char *key, char **arr,
										char **tmp1, char **tmp2)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (key[i])
	{
		if (ft_is_special_char(key[i]))
		{
			*tmp1 = ft_substr(key, 0, i);
			if (!*tmp1)
				return (ft_free_double(arr), 0);
			*tmp2 = ft_substr(key, i, key_len - 1);
			if (!*tmp2)
			{
				free(*tmp1);
				return (ft_free_double(arr), 0);
			}
			break ;
		}
		i++;
	}
	return (1);
}

char	**extract_key_utils(char *key)
{
	char	**arr;
	char	*tmp1;
	char	*tmp2;

	arr = malloc(sizeof(char *) * 3);
	if (!arr)
		return (NULL);
	if (!split_key_on_special_char(key, arr, &tmp1, &tmp2))
		return (NULL);
	arr[0] = ft_strdup(tmp1);
	if (!arr[0])
		return (cleanup_and_return_null(tmp1, tmp2, arr));
	arr[1] = ft_strdup(tmp2);
	if (!arr[1])
		return (cleanup_and_return_null(tmp1, tmp2, arr));
	arr[2] = NULL;
	free (tmp1);
	free (tmp2);
	return (arr);
}
