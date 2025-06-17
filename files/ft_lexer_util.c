/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:09:52 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/04 22:21:05 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_herdoc_flag(t_token **tokenslst)
{
	t_token	*cur;

	if (!tokenslst || !*tokenslst)
		return (0);
	cur = *tokenslst;
	while (cur->next)
		cur = cur->next;
	if (cur->type == HERDC)
		return (1);
	return (0);
}

static int	process_seg(t_segment *cur, char **result, t_data *dt, int her_flag)
{
	char	*tmp;

	if (!cur->in_single && ft_strchr(cur->text, '$') && !her_flag)
	{
		if (expand_segment(cur, dt, result))
			return (1);
	}
	else
	{
		tmp = ft_strjoin(*result, cur->text);
		if (!tmp)
			return (1);
		free(*result);
		*result = tmp;
	}
	return (0);
}

static int	init_segments_and_result(char *str, t_segment **seg, char **result)
{
	*seg = NULL;
	if (ft_split_input_into_segments(str, seg))
		return (1);
	*result = ft_strdup("");
	if (!*result)
	{
		ft_free_segments(*seg);
		return (1);
	}
	return (0);
}

int	ft_check_varible_add_token(t_token **tokenslst, char *str, t_data *dt)
{
	t_segment	*seg;
	t_segment	*cur;
	char		*result;
	int			herdoc_flag;

	if (init_segments_and_result(str, &seg, &result))
		return (1);
	cur = seg;
	herdoc_flag = ft_get_herdoc_flag(tokenslst);
	while (cur)
	{
		if (process_seg(cur, &result, dt, herdoc_flag))
		{
			ft_free_segments(seg);
			return (free(result), 1);
		}
		cur = cur->next;
	}
	ft_add_token(tokenslst, WORD, result);
	free(result);
	ft_free_segments(seg);
	return (0);
}
