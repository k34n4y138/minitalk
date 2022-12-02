/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:36:39 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/01 19:50:22 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	emit_message(char *msg, int spid)
{
	int		i;
	int		len;
	char	hldr;
	int		bititer;

	i = 0;
	len = ft_strlen(msg);
	while (i <= len)
	{
		hldr = msg[i];
		bititer = 7;
		while (bititer >= 0)
		{
			if (kill(spid, SIGUSR1 + ((hldr >> bititer--) & 1)) == -1)
				return (-1);
			usleep(50);
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
		ft_printf("%s: PID doesn't exists %s", av[0],
			"or you don't have permissions to signal this process\n");
	else if (emit_message(av[2], ft_atoi(av[1])) == -1)
		ft_printf("%s: [!]Server crashed existing mid transmission\n", av[0]);
	else
		return (0);
	return (1);
}
