/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:31:51 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/07 14:36:00 by zmoumen          ###   ########.fr       */
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

char	*charapndtostr(char **str, char c, int *strlen)
{
	char	*tofree;
	
	tofree = *str;
	*str = ft_calloc(++(*strlen) + 1, 1);
	if (tofree)
	{
		ft_strlcat(*str, tofree, *strlen + 1);
		free(tofree);
	}
	*str[*strlen - 1] = c;
	return (*str);
}

char	process_bit(t_sigpack *hldr)
{
	char		newbit;
	char		ret;

	newbit = 0;
	ret = 0;
	if (hldr->signal == SIGUSR2)
		newbit = 1;
	acmltr = (hldr->bit_cmltr << 1) | newbit;
	hldr->bit_clk++;
	if (hldr->bit_clk == 8)
	{
		charapndtostr(&(hldr->str), hldr->bit_cmltr, &(hldr->strlen));
		hldr->bit_clk = 0;
		if (hldr->bit_cmltr == 0 || hldr->bit_cmltr == '\n')
		{
			ft_putstr_fd(hldr->str, 1);
			free(hldr->str);
			hldr->strlen = 0;
			ret = hldr->bit_cmltr;
		}
	}
	kill(hldr.cl_pid, hldr.signal);
	return (ret);
}

t_list	*find_signode(t_list *lst,int pid)
{
	while (lst)
	{
		if (((t_sigpack *)lst->content)->cl_pid == pid)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_list	*find_sigstorage(t_list **lst, t_sigpack sigpack)
{
	t_list	*node;
	node = find_signode(*lst, sigpack.cl_pid);
	if (!node)
	{
		node = ft_lstnew(ft_calloc(1, sizeof(t_sigpack)));
		((t_sigpack *)(*lst)->content)->cl_pid = sigpack.cl_pid;
		((t_sigpack *)(*lst)->content)->signal = sigpack.signal;
		ft_lstadd_back(lst, node);
	}
	return (node);
}

void	rem_signode_safely(t_list	**lst, t_list *trgt)
{
	t_list	**hld;
	hld = lst;
	
	trgt
}

void	process_signal(t_sigpack hldr)
{
	static	t_list *sigstorage = 0;
	t_list	*prc_node;
	prc_node = find_sigstorage(&sigstorage, hldr);
	if (prc_node->content)
	{
		
	}	
	// need a bit accomulator, and bit counter
	// need a string storage
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
