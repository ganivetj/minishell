/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:24:20 by jganivet          #+#    #+#             */
/*   Updated: 2021/12/13 12:14:46 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static int	putstr_len(char *s, int len);

int	format_print_char(int i, char *p)
{
	int	padding;
	int	written;

	written = 0;
	padding = flag_value(p, 'W') - 1;
	if (flag_value(p, '-'))
		written += write(1, &i, 1);
	written += pad(' ', padding);
	if (!flag_value(p, '-'))
		written += write(1, &i, 1);
	return (written);
}	

int	format_print_str(char *s, char *p)
{
	int		padding;
	int		len;
	int		written;
	char	pad_style;

	written = 0;
	pad_style = ' ';
	if (flag_value(p, '0') && !flag_value(p, '-'))
		pad_style = '0';
	if (s == NULL)
		s = "(null)";
	if (flag_value(p, '.') && flag_value(p, 'P') < (int)ft_strlen(s))
		len = flag_value(p, 'P');
	else
		len = (int)ft_strlen(s);
	padding = flag_value(p, 'W') - len;
	if (flag_value(p, '-'))
		written += putstr_len(s, len);
	written += pad(pad_style, padding);
	if (!flag_value(p, '-'))
		written += putstr_len(s, len);
	return (written);
}

static int	putstr_len(char *s, int len)
{
	int	i;
	int	written;

	written = 0;
	i = 0;
	while (i < len)
	{
		written += write(1, s + i, 1);
		++i;
	}
	return (written);
}

int	pad(char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		++i;
	}
	return (i);
}

long int	val_abs(long int i)
{
	if (i < 0)
		i *= -1;
	return (i);
}
