/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:51:52 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/08 20:26:27 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

char	*charapndtostr(char *str, char c, int strlen)
{
	str[strlen] = c;
	str[strlen + 1] = 0;
	return (str);
}

t_list	*find_signode(t_list *lst, int pid)
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
		((t_sigpack *)node->content)->cl_pid = sigpack.cl_pid;
		ft_lstadd_back(lst, node);
	}
	((t_sigpack *)(node)->content)->signal = sigpack.signal;
	return (node);
}

void	rem_signode_safely(t_list	**lst, t_list *trgt)
{
	t_list	*hld;
	t_list	*pr_trgt;

	hld = *lst;
	if (hld == trgt)
	{
		hld = trgt->next;
		ft_lstdelone(trgt, free);
	}
	else
	{
		pr_trgt = hld;
		while (pr_trgt)
		{
			if (pr_trgt->next == trgt)
			{
				pr_trgt->next = trgt->next;
				ft_lstdelone(trgt, free);
				break ;
			}
			pr_trgt = pr_trgt->next;
		}
	}
	*lst = hld;
}
