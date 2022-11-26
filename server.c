/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:36:22 by zmoumen           #+#    #+#             */
/*   Updated: 2022/11/26 20:11:45 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	main(int ac, char **av)
{
	int	own_pid;
	struct sigaction a;

	sigaction(SIGUSR1,a,NULL);
	own_pid = getpid();
	ft_printf("server is up with process id: %d \n", own_pid);

	while (1337)
		pause();

	return (0);
}
