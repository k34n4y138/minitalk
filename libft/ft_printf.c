/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:09:42 by zmoumen           #+#    #+#             */
/*   Updated: 2022/11/08 12:08:28 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#define FLAGS "csdiuxX"

static char	*handle_hexa(const char *str, va_list valst)
{
	if (str[1] == 'X')
		return (ft_ultoa_base(va_arg(valst, unsigned int),
				"0123456789ABCDEF", ""));
	if (str[1] == 'x')
		return (ft_ultoa_base(va_arg(valst, unsigned int),
				"0123456789abcdef", ""));
	if (str[1] == 'p')
		return (ft_ultoa_base(va_arg(valst, unsigned long),
				"0123456789abcdef", "0x"));
	else if (str[1] == 'u')
		return (ft_ultoa_base(va_arg(valst, unsigned int),
				"0123456789", ""));
	return (0);
}

static void	aux_printnfree(char *strprint, int *len, char flg)
{
	if (!strprint)
		strprint = ft_strdup("(null)");
	ft_putstr_fd(strprint, 1);
	if (!ft_strlen(strprint) && flg == 'c')
	{
		ft_putchar_fd(0, 1);
		*len += 1;
	}
	else
		*len += ft_strlen(strprint);
	free(strprint);
}

static char	*aux_strdup(const char *s1)
{
	if (s1)
		return (ft_strdup(s1));
	return (NULL);
}

static int	handle_flags(const char *str, va_list valst, int *len)
{
	char	*strprint;
	int		jmplen;

	jmplen = 1;
	strprint = 0;
	if (str[0] == '%' && str[1])
	{
		if (ft_strchr("di", str[1]))
			strprint = ft_itoa(va_arg(valst, int));
		else if (ft_strchr("xXpu", str[1]))
			strprint = handle_hexa(str, valst);
		else if (str[1] == 's')
			strprint = aux_strdup(va_arg(valst, char *));
		else if (str[1] == 'c')
			strprint = ctoa(va_arg(valst, int));
		else
			strprint = ctoa(str[1]);
		jmplen = 2;
	}
	else
		strprint = ctoa(str[0]);
	aux_printnfree(strprint, len, str[1]);
	return (jmplen);
}

int	ft_printf(const char *str, ...)
{
	va_list	valst;
	int		len;
	int		iter;

	len = 0;
	iter = 0;
	va_start(valst, str);
	while (str[iter])
	{
		if (str[iter] == '%' && str[1])
			iter += handle_flags(&str[iter], valst, &len);
		else
		{
			ft_putchar_fd(str[iter++], 1);
			len++;
		}
	}
	return (len);
}
