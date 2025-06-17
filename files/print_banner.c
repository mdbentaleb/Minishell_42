/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_banner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:26:16 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 12:25:02 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	terminal_width(void)
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
	{
		perror("ioctl");
		return (-1);
	}
	return (ws.ws_col);
}

void	utils(char **arr, int term_width)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(arr[0]) / 2;
	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j++ < ((term_width - len) / 2))
			printf(" ");
		printf("%s%s%s\n", GREEN, arr[i], RESET);
		i++;
	}
	j = 0;
	if (term_width < 0)
		term_width = 20;
	while (j++ < (term_width / 2) + 4)
		printf(" ");
	printf("%sversion 1.0.0%s\n", RED, RESET);
}

void	print_banner(void)
{
	char	*arr[6];
	int		term_len;

	term_len = terminal_width();
	arr[0] = "███████╗███╗   ███╗██████╗  █████╗ ███████╗██╗  ██╗";
	arr[1] = "╚══███╔╝████╗ ████║██╔══██╗██╔══██╗██╔════╝██║  ██║";
	arr[2] = "  ███╔╝ ██╔████╔██║██████╔╝███████║███████╗███████║";
	arr[3] = " ███╔╝  ██║╚██╔╝██║██╔══██╗██╔══██║╚════██║██╔══██║";
	arr[4] = "███████╗██║ ╚═╝ ██║██████╔╝██║  ██║███████║██║  ██║";
	arr[5] = "Version 1.0";
	utils(arr, term_len);
}
