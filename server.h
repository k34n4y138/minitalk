/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:58:30 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/07 13:15:54 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "libft/libft.h"
# include <signal.h>

typedef struct sigpack_s
{
	pid_t		cl_pid;
	int			signal;
	char		bit_cmltr;
	int			bit_clk;
	char		*str;
	int			strlen;
}		t_sigpack;

#endif