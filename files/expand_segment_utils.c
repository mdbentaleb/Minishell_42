/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_segment_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:49:10 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/04 12:23:14 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_char(char *s, char c)
{
	int		len;
	char	*new_str;

	len = strlen(s);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, s);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

int	handle_exit_status(t_data *dt, char **result)
{
	char	*val;
	char	*tmp;

	val = ft_itoa(dt->exitstatus);
	if (!val)
		return (1);
	tmp = ft_strjoin(*result, val);
	if (!tmp)
		return (free(val), 1);
	free(*result);
	*result = tmp;
	free(val);
	return (0);
}

int	handle_digit_var(t_data *dt, char **result, char digit)
{
	char	var[2];
	char	*val;
	char	*tmp;

	var[0] = digit;
	var[1] = '\0';
	val = ft_expand_vars(dt, var);
	if (val)
		tmp = ft_strjoin(*result, val);
	else
		tmp = ft_strjoin(*result, "");
	if (!tmp)
	{
		if (val)
			free(val);
		return (1);
	}
	free(*result);
	*result = tmp;
	if (val)
		free(val);
	return (0);
}

int	handle_invalid_var(char **result, t_segment *seg, char *text, int *j)
{
	char	*tmp;

	if (seg->in_double
		|| (seg->next && !seg->next->in_single && !seg->next->in_double)
		|| ((text[*j] == '\0'
				|| ft_is_special_char(text[*j])) && seg->next == NULL))
	{
		tmp = ft_strjoin_char(*result, '$');
		if (!tmp)
			return (1);
		free(*result);
		*result = tmp;
	}
	if (is_special_char(text[*j]))
	{
		tmp = ft_strjoin_char(*result, text[(*j)++]);
		if (!tmp)
			return (1);
		free(*result);
		*result = tmp;
	}
	return (0);
}

int	handle_named_var(t_exp_segm *info)
{
	char	*var;
	char	*tmp;
	char	*expanded;

	var = ft_strndup(&info->seg->text[info->start], *(info->j) - info->start);
	if (!var)
		return (1);
	expanded = ft_expand_vars(info->dt, var);
	free(var);
	if (expanded)
		tmp = ft_strjoin(*(info->result), expanded);
	else
		tmp = ft_strjoin(*(info->result), "");
	if (!tmp)
	{
		if (expanded)
			free(expanded);
		return (1);
	}
	free(*(info->result));
	*(info->result) = tmp;
	if (expanded)
		free(expanded);
	return (0);
}
