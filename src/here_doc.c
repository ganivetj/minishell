/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:44:25 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/28 16:03:45 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_line_null(int fds_read_end, int fds_write_end, char *delimiter);
int	heredoc_ctrlc(int fds_read_end, int fds_write_end);

int	get_here_doc_fd(char *delimiter)
{
	int		fds[2];
	char	*line;

	g_status = 0;
	if (pipe(fds) == -1)
		return (FAILURE);
	while (g_status != CTRL_C)
	{
		modify_signals3();
		line = readline("> ");
		modify_signals();
		if (g_status == CTRL_C)
			return (heredoc_ctrlc(fds[READ_END], fds[WRITE_END]));
		if (line == NULL)
			return (heredoc_line_null(fds[READ_END], fds[WRITE_END],
					delimiter));
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			break ;
		ft_putendl_fd(line, fds[WRITE_END]);
		free(line);
	}
	free(line);
	close(fds[WRITE_END]);
	return (fds[READ_END]);
}

int	heredoc_line_null(int fds_read_end, int fds_write_end, char *delimiter)
{
	close(fds_write_end);
	ft_putstr_fd(HERE_DOC, 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
	return (fds_read_end);
}

int	heredoc_ctrlc(int fds_read_end, int fds_write_end)
{
	close(fds_read_end);
	close(fds_write_end);
	return (HERE_DOC_CTRL_C);
}
