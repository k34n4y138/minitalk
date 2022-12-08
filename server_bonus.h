/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:52:08 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/08 20:27:21 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BONUS_H
# define SERVER_BONUS_H
# include "libft/libft.h"
# include <signal.h>
# define BUFFER_SIZE 2

typedef struct sigpack_s
{
	pid_t		cl_pid;
	int			signal;
	char		bit_cmltr;
	int			bit_clk;
	char		str[BUFFER_SIZE];
	int			strlen;
}		t_sigpack;

char	*charapndtostr(char *str, char c, int strlen);
t_list	*find_signode(t_list *lst, int pid);
t_list	*find_sigstorage(t_list **lst, t_sigpack sigpack);
void	rem_signode_safely(t_list	**lst, t_list *trgt);
#endif