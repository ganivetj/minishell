/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:52:29 by jganivet          #+#    #+#             */
/*   Updated: 2021/12/13 12:15:54 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

static int	print_sign(int i, char *p);
static int	nbrlen(unsigned int n);
static int	putnbr(long int n);

int	format_print_int(int i, char *p)
{
	int	padding;
	int	written;

	written = 0;
	if (flag_value(p, 'P') > nbrlen(val_abs(i)))
		padding = flag_value(p, 'W') - flag_value(p, 'P');
	else
		padding = flag_value(p, 'W') - nbrlen(val_abs(i));
	if (i < 0 || (i >= 0 && (flag_value(p, '+') || flag_value(p, ' '))))
		--padding;
	if (i == 0 && flag_value(p, '.') && flag_value(p, 'P') == 0)
		++padding;
	if (!flag_value(p, '-') && !(!flag_value(p, '.') && flag_value(p, '0')))
		written += pad(' ', padding);
	written += print_sign(i, p);
	if (flag_value(p, '.'))
		written += pad('0', flag_value(p, 'P') - nbrlen(val_abs(i)));
	else if (!flag_value(p, '.') && flag_value(p, '0'))
		written += pad('0', padding);
	if (!(i == 0 && flag_value(p, '.') && flag_value(p, 'P') == 0))
		written += putnbr(i);
	if (flag_value(p, '-') && !(!flag_value(p, '.') && flag_value(p, '0')))
		written += pad(' ', padding);
	return (written);
}

static int	print_sign(int i, char *p)
{
	int	written;

	written = 0;
	if (flag_value(p, '+') && i >= 0)
		written += write(1, "+", 1);
	else if (flag_value(p, ' ') && i >= 0)
		written += write(1, " ", 1);
	else if (i < 0)
		written += write(1, "-", 1);
	return (written);
}

int	format_print_uint(unsigned int i, char *p)
{
	int	padding;
	int	written;

	written = 0;
	if (flag_value(p, 'P') > nbrlen(val_abs(i)))
		padding = flag_value(p, 'W') - flag_value(p, 'P');
	else
		padding = flag_value(p, 'W') - nbrlen(val_abs(i));
	if (flag_value(p, '+') || flag_value(p, ' '))
		--padding;
	if (i == 0 && flag_value(p, '.') && flag_value(p, 'P') == 0)
		++padding;
	if (!flag_value(p, '-') && !(!flag_value(p, '.') && flag_value(p, '0')))
		written += pad(' ', padding);
	if (flag_value(p, '.'))
		written += pad('0', flag_value(p, 'P') - nbrlen(val_abs(i)));
	else if (flag_value(p, '0'))
		written += pad('0', padding);
	if (!(i == 0 && flag_value(p, '.') && flag_value(p, 'P') == 0))
		written += putnbr(i);
	if (flag_value(p, '-') && !(!flag_value(p, '.') && flag_value(p, '0')))
		written += pad(' ', padding);
	return (written);
}

static int	nbrlen(unsigned int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n = n / 10;
		++i;
	}
	return (i);
}

static int	putnbr(long int n)
{
	char	*p;
	int		i;
	int		written;

	n = val_abs(n);
	written = 0;
	p = malloc(32 * sizeof(long int));
	p[0] = 48;
	i = 0;
	while (n > 0)
	{
		p[i] = 48 + (n % 10);
		n = n / 10;
		++i;
	}
	if (i > 0)
		--i;
	while (i >= 0)
	{
		written += write(1, &p[i], 1);
		--i;
	}
	free(p);
	return (written);
}
