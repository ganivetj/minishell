/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:38:23 by jganivet          #+#    #+#             */
/*   Updated: 2021/12/20 17:05:19 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

#define MAX_LINE 100000
#define MAX_FILES 512

char	*get_next_line(int fd)
{
	static char	*store[MAX_FILES];
	char		*ptr;
	int			r;

	if (fd < 0 || fd >= MAX_FILES)
		return (0);
	if (store[fd] == NULL)
		store[fd] = init_store();
	r = 1;
	while(r)
	{
		ptr = get_line(store[fd]);
		if (ptr)
			return (ptr);
		r = store_chunk(fd, store[fd]);	
	}
	ptr = get_store(store[fd]);
	free(store[fd]);
	store[fd] = NULL;
	return(ptr);
}

void	clear_line(char *store)
{
	int	i;
	int	j;
	int	store_len;

	store_len = 0;
	while(store[store_len] != '\0' && store_len < MAX_LINE)
		++store_len;
	i = 0;
	while (store[i] != '\n' && i < store_len)
		++i;
	++i;
	j = i;
	while (j < store_len + i)
	{
		if (j < store_len)
			store[j - i] = store[j];
		else
			store[j - i] = '\0';
		++j;
	}
}

char	*get_line(char *store)
{
	int		i;
	char	*ptr;
	int		j;

	i = 0;
	if (store)
	{
		while (store[i] != '\n' && store[i] != '\0' && i < MAX_LINE - 1)
			++i;
		if (store[i] == '\n')
		{	
			ptr = malloc((i + 2) * sizeof(char));
			j = 0;
			while (j <= i)
			{
				ptr[j] = store[j];
				++j;
			}
			ptr[j] = '\0';
			clear_line(store);
			return (ptr);
		}
	}
	return (0);
}

int	store_chunk(int fd, char *store)
{
	int		r;
	int		i;
	char		*buf;
	int		j;

	buf = malloc(BUFFER_SIZE * sizeof(char));
	r = read(fd, buf, BUFFER_SIZE);
	if (r == 0 || r == -1)
	{
		free(buf);
		return (0);
	}
	i = 0;
	while (store[i] != '\0')
		++i;
	j = 0;
	while (j < r && i + j < MAX_LINE - 1)
	{
		store[i + j] = buf[j];
		++j;
	}
	store[i + j] = '\0';
	free(buf);
	return (r);
}

char	*init_store(void)
{
	char	*ptr;
	int		i;

	ptr = malloc(MAX_LINE * sizeof(char));
	i = 0;
	while (i < MAX_LINE)
	{
		ptr[i] = 0;
		++i;
	}
	return (ptr);
}

char	*get_store(char *store)
{
	int		i;
	char	*ptr;
	int		j;

	i = 0;
	while (store[i] != '\0' && i < MAX_LINE)
		++i;
	if (i >= MAX_LINE)
		return (0);
	if (i)
	{	
		ptr = malloc((i + 2) * sizeof(char));
		j = 0;
		while (j <= i)
		{
			ptr[j] = store[j];
			++j;
		}
		ptr[j] = '\0';
		return (ptr);
	}
	return (0);
}
