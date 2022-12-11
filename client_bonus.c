/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:14:41 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/11 16:19:57 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

int	g_server_ack = 0;

void	server_ack(int sig)
{
	g_server_ack = sig;
}

int	emit_n_wait_ack(int spid, int sent_sig)
{
	static int	graceful_missfire = 0;
	int			retrn;

	if (kill(spid, sent_sig) == -1)
		return (-1);
	if (!g_server_ack)
		sleep(1);
	if (g_server_ack == 0)
	{
		g_server_ack = 0;
		graceful_missfire++;
		retrn = -2;
	}
	else if (g_server_ack != sent_sig)
		retrn = -4;
	else
	{
		g_server_ack = 0;
		graceful_missfire = 0;
		retrn = 0;
	}
	if (retrn == -2 && graceful_missfire == 6)
		retrn = -3;
	usleep(30);
	return (retrn);
}

int	getsig(char bit)
{
	if (bit)
		return (SIGUSR2);
	return (SIGUSR1);
}

int	emit_message(char *msg, int spid)
{
	int		i;
	int		len;
	char	hldr;
	int		bititer;
	int		ackreslt;

	i = 0;
	len = ft_strlen(msg);
	while (i <= len)
	{
		hldr = msg[i];
		bititer = 7;
		while (bititer >= 0)
		{
			ackreslt = emit_n_wait_ack(spid, getsig((hldr >> bititer) & 1));
			if (ackreslt == -2)
				continue ;
			else if (ackreslt == 0)
				bititer--;
			else
				return (ackreslt);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	emmit_res;

	signal(SIGUSR1, server_ack);
	signal(SIGUSR2, server_ack);
	if (ac != 3)
		ft_printf("USAGE: %s [PID] [MESSAGE]\n", av[0]);
	else if (kill(ft_atoi(av[1]), 0) == -1)
		ft_printf("%s: PID doesn't exists %s", av[0],
			"or you don't have permissions to signal this process\n");
	emmit_res = emit_message(av[2], ft_atoi(av[1]));
	if (emmit_res == -1)
		ft_printf("%s: [!] Server crashed!\n", av[0]);
	else if (emmit_res == -4)
		ft_printf("%s: [!] Server didn't acknowledge data properly!\n", av[0]);
	else if (emmit_res == -3)
		ft_printf("%s: [!] TIMEOUT!! server took too long to ack!\n", av[0]);
	else
	{
		ft_printf("%s: [✓] Transmission is finished successfully\n", av[0]);
		return (0);
	}
	return (1);
}
