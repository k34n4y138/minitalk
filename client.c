/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:36:39 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/11 19:43:16 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

void	handler(int sig)
{
	(void)sig;
	usleep(50);
}

int	getsig(char bit)
{
	if (bit)
		return (SIGUSR2);
	return (SIGUSR1);
}

int	emit_message(char *msg, int spid, int strlen)
{
	int		i;
	char	hldr;
	int		bititer;
	int		ret;

	i = 0;
	while (i <= strlen)
	{
		hldr = msg[i];
		bititer = 8;
		while (bititer > 0)
		{
			ret = kill(spid, getsig((hldr >> --bititer) & 1));
			sleep(1);
			if (ret == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	signal(SIGUSR1, handler);
	if (ac != 3)
		ft_printf("USAGE: %s [PID] [MESSAGE]\n", av[0]);
	else if (kill(ft_atoi(av[1]), 0) == -1)
		ft_printf("%s: [!] PID doesn't exists %s", av[0],
			"or you don't have permissions to signal this process\n");
	else if (emit_message(av[2], ft_atoi(av[1]), ft_strlen(av[2])) == -1)
		ft_printf("%s: [!] Server crashed!\n", av[0]);
	else
		ft_printf("%s: [✓] Transmission Finished Successfully\n", av[0]);
	return (0);
}
