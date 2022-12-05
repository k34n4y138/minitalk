/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:31:51 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/05 20:24:34 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

 t_sigpack	g_signal;

void	handler(int sig, siginfo_t *siginfo, void *ctx)
{
	(void)ctx;
	g_signal.cl_pid = siginfo->si_pid;
	g_signal.signal = sig;
}

// void	process_signal(t_sigpack hldr)
// {
// 	static char	acmltr = 0;
// 	static char	cntr = 0;
// 	char		newbit;

// 	newbit = 0;
// 	if (hldr.signal == SIGUSR2)
// 		newbit = 1;
// 	acmltr = (acmltr << 1) | newbit;
// 	cntr++;
// 	if (cntr == 8)
// 	{
// 		write(1, &acmltr, 1);
// 		cntr = 0;
// 	}
// 	kill(hldr.cl_pid, hldr.signal);
// }

void process_signal(t_sigpack hldr)
{
	static char acmltr = 0;
	static char cntr = 0;
	static char *str = NULL;
	static int str_len = 0;
	char newbit;

	newbit = 0;
	if (hldr.signal == SIGUSR2)
		newbit = 1;
	acmltr = (acmltr << 1) | newbit;
	cntr++;
	if (cntr == 8)
	{
		str_len++;
		str = realloc(str, str_len);
		str[str_len - 1] = acmltr;
		if (acmltr == '\0')
		{
			str = realloc(str, str_len + 1);
			str[str_len] = '\0';
			ft_printf("%s\n", str);
			free(str);
			str = 0;
		}
	cntr = 0;
	}
	kill(hldr.cl_pid, hldr.signal);
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
