/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:37:22 by jganivet          #+#    #+#             */
/*   Updated: 2021/12/13 13:15:14 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static int	print_hex_flag(char	*p);
static int	putnbr_hex(unsigned long long n, int uppercase);
static int	nbrlen_hex(unsigned long long n);

int	format_print_ptr(void *ptr, char *p)
{
	int	written;
	int	padding;

	written = 0;
	if (flag_value(p, 'P') > nbrlen_hex((long int)ptr))
		padding = flag_value(p, 'W') - flag_value(p, 'P') - 2;
	else
		padding = flag_value(p, 'W') - nbrlen_hex((long int)ptr) - 2;
	if (ptr == 0 && flag_value(p, '.') && flag_value(p, 'P') == 0)
		++padding;
	if (flag_value(p, '-'))
		written += print_hex_flag(p);
	if (!flag_value(p, '-') && !(!flag_value(p, '.') && flag_value(p, '0')))
		written += pad(' ', padding);
	if (!flag_value(p, '-'))
		written += print_hex_flag(p);
	if (flag_value(p, '.'))
		written += pad('0', flag_value(p, 'P') - nbrlen_hex((long int)ptr));
	else if (flag_value(p, '0'))
		written += pad('0', padding);
	if (!(ptr == 0 && flag_value(p, '.') && flag_value(p, 'P') == 0))
		written += putnbr_hex((unsigned long)ptr, 0);
	if (flag_value(p, '-') && !(!flag_value(p, '.') && flag_value(p, '0')))
		written += pad(' ', padding);
	return (written);
}

int	format_print_hex(unsigned int i, char *p)
{	
	int	padding;
	int	written;

	written = 0;
	if (flag_value(p, 'P') > nbrlen_hex(i))
		padding = flag_value(p, 'W') - flag_value(p, 'P');
	else
		padding = flag_value(p, 'W') - nbrlen_hex(i);
	if (flag_value(p, '#') && i != 0)
		padding = padding - 2;
	if (i == 0 && flag_value(p, '.') && flag_value(p, 'P') == 0)
		++padding;
	if (!flag_value(p, '-') && !(!flag_value(p, '.') && flag_value(p, '0')))
		written += pad(' ', padding);
	if (flag_value(p, '#') && i != 0)
		written += print_hex_flag(p);
	if (flag_value(p, '.'))
		written += pad('0', flag_value(p, 'P') - nbrlen_hex(i));
	else if (flag_value(p, '0'))
		written += pad('0', padding);
	if (!(i == 0 && flag_value(p, '.') && flag_value(p, 'P') == 0))
		written += putnbr_hex(i, flag_value(p, 'X'));
	if (flag_value(p, '-') && !(!flag_value(p, '.') && flag_value(p, '0')))
		written += pad(' ', padding);
	return (written);
}

static int	print_hex_flag(char	*p)
{
	int	written;

	written = 0;
	if (flag_value(p, 'x') || flag_value(p, 'p'))
		written += write(1, "0x", 2);
	else if (flag_value(p, 'X'))
		written += write(1, "0X", 2);
	return (written);
}

static int	putnbr_hex(unsigned long long n, int uppercase)
{
	unsigned long	val;
	char			*alpha;
	int				i;
	int				firstnn;	
	int				written;

	alpha = "0123456789abcdef0123456789ABCDEF";
	written = 0;
	if (n == 0)
		written += write(1, &alpha[0], 1);
	i = 16;
	firstnn = 0;
	while (i > 0)
	{
		val = n / puiss(16, i);
		n -= val * puiss(16, i);
		if (val)
			firstnn = 1;
		if (firstnn)
			written += write(1, &alpha[val + 16 * uppercase], 1);
		--i;
	}
	return (written);
}

static int	nbrlen_hex(unsigned long long n)
{
	unsigned long	val;
	int				i;
	int				firstnn;
	int				decimals;

	decimals = 0;
	i = 16;
	firstnn = 0;
	if (n == 0)
		return (1);
	while (i > 0)
	{
		val = n / puiss(16, i);
		n -= val * puiss(16, i);
		if (val)
			firstnn = 1;
		if (firstnn)
			++decimals;
		--i;
	}
	return (decimals);
}
