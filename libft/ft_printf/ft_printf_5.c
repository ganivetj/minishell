/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:02:05 by jganivet          #+#    #+#             */
/*   Updated: 2021/12/09 11:39:30 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

unsigned long	puiss(int base, int n)
{
	unsigned long	r;

	r = 1;
	while (n - 1)
	{
		r *= base;
		--n;
	}
	return (r);
}

int	format_print_percent(char *p)
{
	int	written;
	int	padding;
	int	pad_style;

	written = 0;
	padding = flag_value(p, 'W') - 1;
	if (flag_value(p, '0'))
		pad_style = '0';
	else
		pad_style = ' ';
	if (!flag_value(p, '-'))
		written += pad(pad_style, padding);
	written += write(1, "%", 1);
	if (flag_value(p, '-'))
		written += pad(' ', padding);
	return (written);
}
