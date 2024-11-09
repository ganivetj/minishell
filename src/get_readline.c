/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:33:03 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/28 15:43:55 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE  // Enables GNU extensions, might be necessary for some readline functions
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static char	*get_readline_2(char *prompt_message, char *previous_entry);
static int	make_prompt_message(char **prompt_message,
				t_env_list *env_list_head);
static int	only_contains_whitespaces(char *entry);
static int	make_prompt_message2(char **prompt_message, char *pwd);

/* The functions get_readline and get_readline_2 take as an argument a prompt
** message, then display this message and wait for a user entry. Then it checks
** if the entry is the same as the previous entry. If it is not the case, the
** new entry is added to the entries history list. */
int	get_readline(char **line, t_env_list *env_list_head)
{
	char	*previous_entry;
	char	*prompt_message;

	if (make_prompt_message(&prompt_message, env_list_head) == FAILURE)
		return (FAILURE);
	previous_entry = NULL;
	if (rl_line_buffer != NULL)
	{
		previous_entry = ft_strdup(rl_line_buffer);
		if (previous_entry == NULL)
		{
			free(prompt_message);
			return (err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR));
		}
	}
	*line = get_readline_2(prompt_message, previous_entry);
	if (*line == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static char	*get_readline_2(char *prompt_message, char *previous_entry)
{
	char	*entry;

	entry = readline(prompt_message);
	free(prompt_message);
	if (entry == NULL)
	{
		free(previous_entry);
		err_handler(NULL, NO_FREE, EXIT, g_status);
		return (NULL);
	}
	if (only_contains_whitespaces(entry) == 1 && previous_entry != NULL)
		rl_replace_line(previous_entry, 0);
	if (previous_entry == NULL && only_contains_whitespaces(entry) == 0)
		add_history(entry);
	else if (only_contains_whitespaces(entry) == 0
		&& ft_strncmp(entry, previous_entry, ft_strlen(entry) + 1) != 0)
		add_history(entry);
	free(previous_entry);
	return (entry);
}

/* The functions make_prompt_message takes the username and the current working
** directory from the environment list and creates a prompt message string
** of the form: "username@minishell:working_directory$ " */
static int	make_prompt_message(char **prompt_message,
				t_env_list *env_list_head)
{
	char	*pwd;
	char	*username;

	username = get_env_val(env_list_head, "USER");
	if (username == NULL)
		return (err_handler(NULL, NO_FREE, NO_USR, GENERAL_ERR));
	*prompt_message = ft_strjoin(username, "@minishell:");
	free(username);
	if (*prompt_message == NULL)
		return (err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR));
	pwd = get_env_val(env_list_head, "PWD");
	if (pwd == NULL)
	{
		free(*prompt_message);
		return (err_handler(NULL, NO_FREE, NO_PWD, GENERAL_ERR));
	}
	return (make_prompt_message2(prompt_message, pwd));
}	

static int	make_prompt_message2(char **prompt_message, char *pwd)
{	
	char	*aux_prompt_message;

	aux_prompt_message = ft_strjoin(*prompt_message, pwd);
	free(pwd);
	free(*prompt_message);
	if (aux_prompt_message == NULL)
		return (err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR));
	*prompt_message = ft_strjoin(aux_prompt_message, "$ ");
	free(aux_prompt_message);
	if (*prompt_message == NULL)
		return (err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR));
	return (SUCCESS);
}

/* If the read line contains only whitespaces, the line shall not be saved
** into the history list. */
static int	only_contains_whitespaces(char *entry)
{
	while (ft_isspace(*entry))
		++entry;
	if (*entry != '\0')
		return (0);
	return (1);
}
