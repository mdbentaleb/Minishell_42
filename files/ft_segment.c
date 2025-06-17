/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_segment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:47:17 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 15:49:12 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_add_segment(t_segment **head, char *text, bool in_single, bool in_double)
{
	t_segment	*new;
	t_segment	*cur;

	new = malloc(sizeof(t_segment));
	if (!new)
		return (1);
	new->text = text;
	new->in_single = in_single;
	new->in_double = in_double;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return (0);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (0);
}

static int	add_single_segment(char *input, int *i, t_segment **segments)
{
	int	start;

	start = ++(*i);
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (ft_add_segment(segments,
			ft_strndup(input + start, *i - start), true, false))
		return (1);
	if (input[*i] == '\'')
		(*i)++;
	return (0);
}

static int	add_double_segment(char *input, int *i, t_segment **segments)
{
	int	start;

	start = ++(*i);
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (ft_add_segment(segments,
			ft_strndup(input + start, *i - start), false, true))
		return (1);
	if (input[*i] == '"')
		(*i)++;
	return (0);
}

static int	add_word_segment(char *input, int *i, t_segment **segments)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != ' '
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	if (ft_add_segment(segments,
			ft_strndup(input + start, *i - start), false, false))
		return (1);
	return (0);
}

int	ft_split_input_into_segments(char *input, t_segment **segments)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			if (add_single_segment(input, &i, segments))
				return (1);
		}
		else if (input[i] == '"')
		{
			if (add_double_segment(input, &i, segments))
				return (1);
		}
		else if (input[i] == ' ')
			i++;
		else
		{
			if (add_word_segment(input, &i, segments))
				return (1);
		}
	}
	return (0);
}
