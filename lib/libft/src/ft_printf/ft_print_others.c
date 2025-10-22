/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_others.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armandanger <armandanger@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:02:31 by aranger           #+#    #+#             */
/*   Updated: 2025/10/21 21:15:24 by armandanger      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_size_int(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	n = n / 10;
	i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

size_t	ft_print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

size_t	ft_print_string(char *str)
{
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_print_decimal(int nbr)
{
	ft_putnbr_fd(nbr, 1);
	return (ft_size_int(nbr));
}

static int	ft_putnbr_unsigned_rec(size_t n)
{
	char	c;
	int		count;

	count = 0;
	if (n >= 10)
		count += ft_putnbr_unsigned_rec(n / 10);
	c = (n % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}

int	ft_print_size_t(size_t n)
{
	return (ft_putnbr_unsigned_rec(n));
}
