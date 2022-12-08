/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:14:41 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/08 19:02:27 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

int	g_serve_ack = 0;

void	server_ack(int sig)
{
	g_serve_ack = sig;
}

int	pause_n_wait_server(int sent_sig)
{
	sleep(1);
	if (g_serve_ack != sent_sig)
		return (-1);
	g_serve_ack = 0;
	return (0);
}

int	emit_message(char *msg, int spid)
{
	int		i;
	int		len;
	char	hldr;
	int		bititer;
	int		trgtsig;

	i = 0;
	len = ft_strlen(msg);
	while (i <= len)
	{
		hldr = msg[i];
		bititer = 7;
		while (bititer >= 0)
		{
			trgtsig = SIGUSR1;
			if ((hldr >> bititer--) & 1)
				trgtsig = SIGUSR2;
			if (kill(spid, trgtsig) == -1
				|| pause_n_wait_server(trgtsig) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	signal(SIGUSR1, server_ack);
	signal(SIGUSR2, server_ack);
	if (ac != 3)
		ft_printf("USAGE: %s [PID] [MESSAGE]\n", av[0]);
	else if (kill(ft_atoi(av[1]), 0) == -1)
		ft_printf("%s: PID doesn't exists %s", av[0],
			"or you don't have permissions to signal this process\n");
	else if (emit_message(av[2], ft_atoi(av[1])) == -1)
		ft_printf("%s: [!]Server didn't acknowledge data properly!\n", av[0]);
	else
		ft_printf("%s: [✓]Transmission has finished successfully", av[0]);
	return (1);
}
