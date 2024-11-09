/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:33:03 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/30 14:19:50 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	main_2(int argc, char **argv, t_env_list *env_list_head);
static int	main_3(char ***tokens, t_env_list *env_list_head);
static int	main_4(char **tokens, t_env_list *env_list_head);

int	g_status;

int	main(int argc, char *argv[], char *envp[])
{
	t_env_list	*env_list_head;

	g_status = 0;
	if (modify_sigquit() == FAILURE)
		return (g_status);
	env_list_head = cpy_envp_to_env_list(envp);
	if (env_list_head == NULL)
	{
		err_handler(0, NO_FREE, NO_ENV, GENERAL_ERR);
		return (g_status);
	}
	return (main_2(argc, argv, env_list_head));
}

static int	main_2(int argc, char **argv, t_env_list *env_list_head)
{
	int			err_num;
	char		**tokens;

	while (argc != 0 && argv != NULL)
	{
		err_num = main_3(&tokens, env_list_head);
		if (err_num == FAILURE)
			return (g_status);
		else if (err_num == FT_CONTINUE)
			continue ;
		if (check_tokens(tokens) == FT_CONTINUE)
		{
			ft_free_2d_char_array(tokens);
			continue ;
		}
		err_num = main_4(tokens, env_list_head);
		if (err_num == FAILURE)
			return (g_status);
	}
	return (g_status);
}

static int	main_3(char ***tokens, t_env_list *env_list_head)
{
	int		err_num;
	char	*line;

	if (modify_signals2() == FAILURE)
		return (FAILURE);
	if (get_readline(&line, env_list_head) == FAILURE)
	{
		free_env_list(env_list_head);
		return (FAILURE);
	}
	if (modify_signals() == FAILURE)
		return (FAILURE);
	err_num = split_tokens(tokens, &line);
	free(line);
	if (err_num == FAILURE)
		free_env_list(env_list_head);
	return (err_num);
}

static int	main_4(char **tokens, t_env_list *env_list_head)
{
	int			err_num;
	t_prompt	*prompt;

	if (expand_array(tokens, env_list_head))
	{
		ft_free_2d_char_array(tokens);
		free_env_list(env_list_head);
		return (FAILURE);
	}
	err_num = parser(&prompt, tokens);
	ft_free_2d_char_array(tokens);
	if (err_num == FAILURE)
	{
		free_env_list(env_list_head);
		return (FAILURE);
	}
	else if (err_num == FT_CONTINUE)
		return (FT_CONTINUE);
	prompt->env_list = env_list_head;
	err_num = executor(&prompt);
	free(prompt);
	if (err_num == FAILURE)
		free_env_list(env_list_head);
	return (err_num);
}
