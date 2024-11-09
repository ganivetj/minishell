/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:07:06 by jganivet          #+#    #+#             */
/*   Updated: 2021/12/20 12:05:03 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

char	*get_next_line(int fd);
char	*init_store(void);
int		store_chunk(int fd, char *store);
char	*get_line(char *store);
void	clear_line(char *store);
char	*get_store(char *store);

#endif
