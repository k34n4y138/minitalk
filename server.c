/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:48:12 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/05 18:12:40 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	g_signal;

void	handler(int sig)
{
	g_signal = sig;
}

void	process_signal(int hldr)
{
	static char	acmltr = 0;
	static char	cntr = 0;
	char		newbit;

	newbit = 0;
	if (hldr == SIGUSR2)
		newbit = 1;
	acmltr = (acmltr << 1) | newbit;
	cntr++;
	if (cntr == 8)
	{
		write(1, &acmltr, 1);
		cntr = 0;
	}
}

int	main(void)
{
	pid_t				serverpid;

	serverpid = getpid();
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	ft_printf("server is up and running with process id: %d\n", serverpid);
	while (1)
	{
		pause();
		process_signal(g_signal);
	}
}
