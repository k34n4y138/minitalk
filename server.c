/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:48:12 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/12 17:08:58 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

struct	s_signal {
	int	cl_pid;
	int	signal;
	int	new;
}		g_signal = {0};

void	handler(int sig, siginfo_t *siginfo, void *ctx)
{
	if (g_signal.new)
		return ;
	g_signal.cl_pid = siginfo->si_pid;
	g_signal.signal = sig;
	g_signal.new = 1;
	(void)ctx;
}

void	process_signal(int rxsig, int cl_pid)
{
	static char	acmltr = 0;
	static char	cntr = 0;
	static int	last_sender = 0;
	char		newbit;

	g_signal.new = 0;
	if (last_sender != cl_pid)
	{
		last_sender = cl_pid;
		cntr = 0;
	}
	newbit = 0;
	if (rxsig == SIGUSR2)
		newbit = 1;
	acmltr = (acmltr << 1) | newbit;
	cntr++;
	if (cntr > 7)
	{
		write(1, &acmltr, 1);
		cntr = 0;
	}
	usleep(60);
	kill(cl_pid, SIGUSR1);
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
		if (!g_signal.new)
			pause();
		process_signal(g_signal.signal, g_signal.cl_pid);
	}
}
