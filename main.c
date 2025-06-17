/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:30:16 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 12:12:32 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_prompt(t_data *dt)
{
	while (1)
	{
		dt->input = readline("zmbash-2.5$ ");
		ft_add_history(dt);
		if (!dt->input || ft_str_trim_n_cmp(dt->input, "exit", 4) == 0)
		{
			ft_builtin_exit(dt);
			continue ;
		}
		dt->lsttoken = NULL;
		if (check_pre_lexing_errors(dt))
		{
			dt->exitstatus = 2;
			free(dt->input);
			dt->input = NULL;
			continue ;
		}
		dt->cmdlst = ft_lexer(&dt->lsttoken, dt);
		if (exec_command(dt->cmdlst, dt))
		{
			ft_free_cmd(dt->cmdlst);
			continue ;
		}
		ft_free_cmd(dt->cmdlst);
	}
}

int	main(int arc, char **arv, char **env)
{
	t_data	dt;

	(void)arv;
	ft_signals();
	if (ft_init_data(&dt, arc, env))
	{
		ft_free_env(dt.env);
		return (1);
	}
	read_prompt(&dt);
	return (0);
}
