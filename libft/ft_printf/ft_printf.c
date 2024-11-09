/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:58:38 by jganivet          #+#    #+#             */
/*   Updated: 2021/12/13 12:17:32 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

static int	dispatch_type(char *p, va_list ap);
static int	flag_value_2(char *s, char f, int i);

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	char	*p;
	int		written;

	va_start(ap, fmt);
	p = (char *)fmt;
	written = 0;
	while (*p)
	{
		if (*p != '%')
		{
			written += write(1, p, 1);
			++p;
			continue ;
		}
		++p;
		written += dispatch_type(p, ap);
		if (is_in_str("csdiupxX%", flag_value(p, 'S')))
			p += flag_value(p, 'L');
	}
	va_end(ap);
	return (written);
}

int	is_in_str(char *s, char c)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == c)
			return (1);
		++i;
	}
	return (0);
}

static int	dispatch_type(char *p, va_list ap)
{
	int	written;

	written = 0;
	if (flag_value(p, 'c'))
		written += format_print_char(va_arg(ap, int), p);
	else if (flag_value(p, 's'))
		written += format_print_str(va_arg(ap, char *), p);
	else if (is_in_str("di", flag_value(p, 'S')))
		written += format_print_int(va_arg(ap, int), p);
	else if (flag_value(p, 'u'))
		written += format_print_uint(va_arg(ap, unsigned int), p);
	else if (flag_value(p, 'p'))
		written += format_print_ptr(va_arg(ap, void *), p);
	else if (is_in_str("xX", flag_value(p, 'S')))
		written += format_print_hex(va_arg(ap, unsigned int), p);
	else if (flag_value(p, '%'))
		written += format_print_percent(p);
	else
		written += write(1, "%", 1);
	return (written);
}

int	flag_value(char *s, char f)
{
	int	i;

	i = 0;
	while (is_in_str(" +0#-", s[i]))
	{
		if (s[i++] == f)
			return (1);
	}
	if (f == 'W')
		return (ft_atoi(&s[i]));
	while (ft_isdigit(s[i]))
		++i;
	return (flag_value_2(s, f, i));
}

static int	flag_value_2(char *s, char f, int i)
{
	if (s[i] == '.')
	{
		if (f == '.')
			return (1);
		if (f == 'P')
			return (ft_atoi(&s[i + 1]));
		++i;
		while (ft_isdigit(s[i]))
			++i;
	}
	if (f == 'S')
		return (s[i]);
	if (f == s[i])
		return (1);
	if (f == 'L')
		return (i + 1);
	return (0);
}
