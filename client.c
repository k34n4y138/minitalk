/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:36:39 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/10 10:21:41 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

int	emit_message(char *msg, int spid)
{
	int		i;
	int		len;
	char	hldr;
	int		bititer;
	int		txsig;

	i = 0;
	len = ft_strlen(msg);
	while (i <= len)
	{
		hldr = msg[i];
		bititer = 8;
		while (bititer > 0)
		{
			txsig = SIGUSR1;
			if ((hldr >> --bititer) & 1)
				txsig = SIGUSR2;
			if (kill(spid, txsig) == -1)
				return (-1);
			usleep(100);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 3)
		ft_printf("USAGE: %s [PID] [MESSAGE]\n", av[0]);
	else if (kill(ft_atoi(av[1]), 0) == -1)
		ft_printf("%s: [!] PID doesn't exists %s", av[0],
			"or you don't have permissions to signal this process\n");
	else if (emit_message(av[2], ft_atoi(av[1])) == -1)
		ft_printf("%s: [!] Server crashed!\n", av[0]);
	else
		ft_printf("%s: [✓] Transmission Finished Successfully\n", av[0]);
	return (0);
}
