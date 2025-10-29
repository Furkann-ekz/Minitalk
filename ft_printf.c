/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fekiz <fekiz@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:53:49 by fekiz             #+#    #+#             */
/*   Updated: 2025/10/26 18:54:00 by fekiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!(str))
	{
		count += write(1, "(null)", 6);
		return (count);
	}
	while (str[i])
	{
		count += ft_putchar(str[i]);
		i++;
	}
	return (count);
}

int	ft_putnbr(int n)
{
	long	num;
	int		count;

	count = 0;
	num = n;
	if (num < 0)
	{
		count += ft_putchar('-');
		num *= -1;
	}
	if (num < 10)
		count += ft_putchar(num + '0');
	else
	{
		count += ft_putnbr(num / 10);
		count += ft_putnbr(num % 10);
	}
	return (count);
}

int	type(char c, va_list list)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar(va_arg(list, int));
	else if (c == 's')
		len += ft_putstr(va_arg(list, char *));
	else if (c == 'd')
		len += ft_putnbr(va_arg(list, int));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			type(str[i + 1], list);
			i += 2;
		}
		else
		{
			len += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(list);
	return (len);
}
