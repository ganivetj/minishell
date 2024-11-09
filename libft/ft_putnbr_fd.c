/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:29:50 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/22 10:02:48 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int base, int exp);
static int	get_offset(int n);
static int	final_len(int n);

void	ft_putnbr_fd(int n, int fd)
{
	int			i;
	long int	j;
	char		c;

	j = (long int)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		j *= -1;
	}
	i = final_len(n) - 1 - get_offset(n);
	while (i >= 0)
	{
		c = 48 + j / ft_pow(10, i);
		write(fd, &c, 1);
		j = j - j / ft_pow(10, i) * ft_pow(10, i);
		--i;
	}
}

static int	ft_pow(int base, int exp)
{
	int	i;
	int	r;

	r = 1;
	i = 0;
	while (i < exp)
	{
		r = r * base;
		++i;
	}
	return (r);
}

static int	get_offset(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static int	final_len(int n)
{
	int	l;
	int	i;

	if (n == 0)
		return (1);
	l = 1;
	if (n < 0)
		l = 2;
	i = 9;
	while (i >= 0)
	{
		if (n / ft_pow(10, i) != 0)
		{
			l += i;
			return (l);
		}
		--i;
	}
	return (i);
}
