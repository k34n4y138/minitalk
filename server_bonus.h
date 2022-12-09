/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:52:08 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/09 19:29:58 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BONUS_H
# define SERVER_BONUS_H
# include "libft/libft.h"
# include <signal.h>
# define BUFFER_SIZE 512
# define SIGPACKS_ARRSIZE 512

typedef struct sigpack_s
{
	int			signal;
	char		bit_cmltr;
	int			bit_clk;
	char		str[BUFFER_SIZE];
	int			strlen;
	int			new;
	int			cl_pid;
}		t_sigpack;
#endif