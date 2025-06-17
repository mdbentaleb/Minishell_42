/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:13:26 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/05 14:32:21 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_handle_name(t_exp_segm info)
{
	while (info.seg->text[*(info.j)] && (ft_isalnum(info.seg->text[*(info.j)])
			|| info.seg->text[*(info.j)] == '_'))
		(*(info.j))++;
	if (info.start == *(info.j))
	{
		if (handle_invalid_var(info.result, info.seg, info.seg->text, info.j))
			return (1);
	}
	else
	{
		if (handle_named_var(&info))
			return (1);
	}
	return (0);
}

static void	init_info(t_exp_segm *info, int *j, int *start, char **result)
{
	info->j = j;
	info->start = *start;
	info->result = result;
}

static int	handle_dollar(t_segment *seg, t_data *dt, char **result, int *j)
{
	t_exp_segm	info;
	int			start;

	start = *j;
	if (seg->text[*j] == '?')
	{
		if (handle_exit_status(dt, result))
			return (1);
		(*j)++;
	}
	else if (ft_isdigit(seg->text[*j]))
	{
		if (handle_digit_var(dt, result, seg->text[*j]))
			return (1);
		(*j)++;
	}
	else
	{
		info.seg = seg;
		info.dt = dt;
		init_info(&info, j, &start, result);
		if (ft_handle_name(info))
			return (1);
	}
	return (0);
}

int	expand_segment(t_segment *seg, t_data *dt, char **result)
{
	int		j;
	char	*tmp;

	j = 0;
	while (seg->text[j])
	{
		if (seg->text[j] == '$')
		{
			j++;
			if (handle_dollar(seg, dt, result, &j))
				return (1);
		}
		else
		{
			tmp = ft_strjoin_char(*result, seg->text[j++]);
			if (!tmp)
				return (1);
			free(*result);
			*result = tmp;
		}
	}
	return (0);
}
