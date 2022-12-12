/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:40:11 by zmoumen           #+#    #+#             */
/*   Updated: 2022/12/12 16:55:26 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

int	can_inject_unicode(t_sigpack *hldr)
{
	int	len;
	int	iter;

	iter = 6;
	len = 1;
	if ((hldr->bit_cmltr >> iter-- & 1))
		len++;
	return (len);
	if (BUFFER_SIZE - hldr->strlen - 1 >= hldr->bit_cmltr)
		return (1);
	return (0);
}
