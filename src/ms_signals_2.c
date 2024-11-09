/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:24:52 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/28 12:39:20 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modify_signals(void)
{
	struct sigaction	sa_sigint;

	sa_sigint.sa_handler = &handle_ctrlc_outside_rl;
	sa_sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
		return (err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR));
	return (SUCCESS);
}

int	modify_signals2(void)
{
	struct sigaction	sa_sigint;

	sa_sigint.sa_handler = &handle_ctrlc_inside_rl;
	sa_sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
		return (err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR));
	return (SUCCESS);
}

int	modify_signals3(void)
{
	struct sigaction	sa_sigint;

	sa_sigint.sa_handler = &handle_ctrlc_inside_heredoc;
	sa_sigint.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_sigint, NULL) == -1)
		return (err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR));
	return (SUCCESS);
}

int	modify_sigquit(void)
{
	struct sigaction	sa_sigquit;

	rl_catch_signals = 0;
	sa_sigquit.sa_handler = SIG_IGN;
	sa_sigquit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_sigquit, NULL) == -1)
		return (err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR));
	return (SUCCESS);
}
