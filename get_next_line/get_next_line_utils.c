/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:51:07 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 11:10:12 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_get(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr_get(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen_get(s))
		return (ft_strdup_get(""));
	if ((ft_strlen_get(s) - start) < len)
		ptr = malloc(sizeof(char) * (ft_strlen_get(s) - start + 1));
	else
		ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*(s + start + i) && (len > 0))
	{
		*(ptr + i) = *(s + start + i);
		i++;
		len--;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

char	*ft_strdup_get(const char *s1)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)(malloc(sizeof(char) * (ft_strlen_get(s1) + 1)));
	if (!tmp)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strchr_get(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin_get(char const *s1, char const *s2)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(char) * (ft_strlen_get(s1) + ft_strlen_get(s2) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		tmp[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		tmp[j++] = s2[i++];
	tmp[j] = '\0';
	free((char *)s1);
	return (tmp);
}
