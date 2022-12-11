/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:48:57 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/11 16:28:00 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

t_sigpack	g_signal = {0};

void	handler(int sig, siginfo_t *siginfo, void *ctx)
{
	if (g_signal.new)
		return ;
	g_signal.new = 1;
	g_signal.cl_pid = siginfo->si_pid;
	g_signal.signal = sig;
	(void)ctx;
}

t_sigpack	*find_sigpack(t_sigpack strg[], int cl_pid)
{
	int			idx;

	idx = 0;
	while (idx < SIGPACKS_ARRSIZE)
	{
		if (strg[idx].cl_pid == cl_pid)
			return (&strg[idx]);
		idx++;
	}
	idx = 0;
	while (idx <= SIGPACKS_ARRSIZE)
	{
		if (strg[idx].cl_pid == 0)
		{
			strg[idx].cl_pid = cl_pid;
			return (&strg[idx]);
		}
		idx++;
	}
	return (NULL);
}

int	process_bit(t_sigpack *hldr)
{
	char		newbit;

	newbit = 0;
	if (hldr->signal == SIGUSR2)
		newbit = 1;
	hldr->bit_cmltr = (hldr->bit_cmltr << 1) | newbit;
	hldr->bit_clk++;
	if (hldr->bit_clk == 8)
	{
		hldr->str[(hldr->strlen)++] = hldr->bit_cmltr;
		hldr->bit_clk = 0;
		if (hldr->bit_cmltr == 0 || hldr->bit_cmltr == '\n'
			|| hldr->strlen >= BUFFER_SIZE - 1)
		{
			write(1, hldr->str, hldr->strlen);
			hldr->strlen = 0;
			return (1);
		}
	}
	return (0);
}

void	process_signal(int cl_pid, int newsig)
{
	static t_sigpack	storage[SIGPACKS_ARRSIZE] = {0};
	static t_sigpack	*last_sender = NULL;

	g_signal.new = 0;
	if (!last_sender
		|| (last_sender && last_sender->cl_pid != cl_pid))
		last_sender = find_sigpack(storage, cl_pid);
	if (!last_sender)
		return ;
	last_sender->signal = newsig;
	if (process_bit(last_sender))
		last_sender->cl_pid = 0;
	usleep(30);
	kill(cl_pid, newsig);
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
	g_signal.new = 0;
	ft_printf("server is up and running with process id: %d\n", serverpid);
	while (1)
	{
		if (!g_signal.new)
			pause();
		process_signal(g_signal.cl_pid, g_signal.signal);
	}
}
