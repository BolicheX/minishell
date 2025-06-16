/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:13:45 by jose-jim          #+#    #+#             */
/*   Updated: 2024/10/31 14:51:57 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	format(char conv, va_list arg)
{
	int	i;

	i = 0;
	if (conv == 'c')
		i += ft_putchar(va_arg(arg, int));
	else if (conv == 's')
		i += ft_putstr(va_arg(arg, char *));
	else if (conv == 'p')
		i += ft_putptr((unsigned long)va_arg(arg, void *));
	else if (conv == 'd' || conv == 'i')
		i += ft_putnbr(va_arg(arg, int));
	else if (conv == 'u')
		i += ft_putnbr_unsign(va_arg(arg, int));
	else if (conv == 'x' || conv == 'X')
		i += ft_puthex(va_arg(arg, unsigned long int), conv);
	else if (conv == '%')
		i += write(1, "%", 1);
	else
		return (-1);
	return (i);
}

int	ft_printf(char const *s, ...)
{
	va_list	arg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(arg, s);
	while (*s)
	{
		if (*s != '%')
			i += write(1, s, 1);
		else
		{
			j = format(*(++s), arg);
			if (j < 0)
				return (-1);
			else
				i = i + j;
		}
		s++;
	}
	va_end(arg);
	return (i);
}
