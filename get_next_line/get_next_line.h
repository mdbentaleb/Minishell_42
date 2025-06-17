/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:51:15 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 11:10:28 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

size_t	ft_strlen_get(const char *s);
char	*ft_substr_get(char const *s, unsigned int start, size_t len);
char	*ft_strchr_get(const char *s, int c);
char	*ft_strdup_get(const char *s);
char	*ft_strjoin_get(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif