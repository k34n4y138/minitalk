/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:31:51 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/08 20:01:12 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

t_sigpack	g_signal;

void	handler(int sig, siginfo_t *siginfo, void *ctx)
{
	(void)ctx;
	g_signal.cl_pid = siginfo->si_pid;
	g_signal.signal = sig;
}

char	process_bit(t_sigpack *hldr)
{
	char		newbit;
	char		ret;

	newbit = 0;
	ret = 0;
	if (hldr->signal == SIGUSR2)
		newbit = 1;
	hldr->bit_cmltr = (hldr->bit_cmltr << 1) | newbit;
	hldr->bit_clk++;
	if (hldr->bit_clk == 8)
	{
		charapndtostr(hldr->str, hldr->bit_cmltr, (hldr->strlen)++);
		hldr->bit_clk = 0;
		if (hldr->bit_cmltr == 0 || hldr->bit_cmltr == '\n'
			|| hldr->strlen == BUFFER_SIZE - 1)
		{
			ft_putstr_fd(hldr->str, 1);
			ret = 1;
			hldr->bit_cmltr = 0;
		}
	}
	kill(hldr->cl_pid, hldr->signal);
	return (ret);
}

void	process_signal(t_sigpack hldr)
{
	static t_list	*sigstorage = 0;
	t_list			*prc_node;

	prc_node = find_sigstorage(&sigstorage, hldr);
	if (process_bit(prc_node->content))
		rem_signode_safely(&sigstorage, prc_node);
}

int	main(void)
{
	pid_t				serverpid;
	struct sigaction	sigact;

	serverpid = getpid();
	sigact.sa_sigaction = handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	ft_printf("server is up and running with process id: %d\n", serverpid);
	while (1)
	{
		pause();
		process_signal(g_signal);
	}
}
