/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:38:57 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/17 13:01:41 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		final_len(int i);
static int		ft_pow(int base, int exp);
static int		get_offset(int n);
int				ft_abs(int n);

char	*ft_itoa(int n)
{
	int				i;
	char			*r;
	long int		j;
	int				str_idx;

	r = malloc(final_len(n) + 1);
	if (r == NULL)
		return (NULL);
	if (n == 0)
		r[0] = 48;
	str_idx = 0;
	j = (long int)n;
	j = ft_abs(j);
	if (n < 0)
		r[str_idx++] = '-';
	i = final_len(n) - 1 - get_offset(n);
	while (i >= 0)
	{
		r[str_idx++] = 48 + j / ft_pow(10, i);
		j = j - j / ft_pow(10, i) * ft_pow(10, i);
		--i;
	}
	r[final_len(n)] = '\0';
	return (r);
}

int ft_abs(int n)
{
    if (n < 0)
        n = n * -1;
    return (n);
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
