/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:58:30 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/05 19:46:39 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "libft/libft.h"
# include <signal.h>

typedef struct sigpack_s
{
	pid_t	cl_pid;
	int		signal;
}		t_sigpack;

#endif