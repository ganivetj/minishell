/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:34:15 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/30 15:57:55 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <ctype.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>

# define READ_END	0
# define WRITE_END	1
# define PERROR		"Use original perror function !"
# define PERROR_2	"Use original perror function + path name!"
# define NO_USR		"No username found in the shell environment !"
# define NO_PWD		"No working directory found in the shell environment !"
# define NO_PATH	"No path found in the shell environment !"
# define EXIT		"exit"
# define QUOTES		"Quotes are not closed !"
# define NO_TOKENS	"There isn't any token !"
# define NO_ARG		"The argument is NULL !"
# define NO_FILENAM	"Missing filename for redirection !"
# define CMD_NO_FND	": command not found"
# define NO_ENV		"-minishell: cannot import environment variables"
# define HERE_DOC	"-minishell: warning: here-document delimited by "
# define SYNTAX_1	"-minishell: syntax error near unexpected token `|'"
# define SYNTAX_2	"-minishell: syntax error with redirection operators"
# define IS_DIR		": Is a directory"
# define NO_FILE	": no such file or directory"

extern int	g_status;

typedef struct s_prompt
{
	struct s_list		*cmds;
	struct s_env_list	*env_list;
}						t_prompt;

typedef struct s_list
{
	int				pid;
	int				is_builtin;
	int				pipes[2];
	int				input;
	int				output;
	char			*open_err;
	char			*full_path;
	char			**full_cmd;
	struct s_list	*next_cmd;
}					t_list;

typedef struct s_env_list
{
	int					marked;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_container
{
	int	i;
	int	j;
	int	err_num;
}		t_container;

enum	e_error_code
{
	HERE_DOC_CTRL_C = -4,
	FAILURE = -3,
	FT_CONTINUE_2 = -2,
	FT_CONTINUE = -1,
	SUCCESS = 0,
	GENERAL_ERR = 1,
	GEN = 1,
	CMD_ERR = 2,
	FREE_LIST_CMD = 3,
	FREE_LC = 3,
	NO_FREE,
	FREE_LIST,
	FREE_LIST_CMD_PATH,
	FREE_ALL,
	FREE_ALL_PATH,
	NO_PERMISSION = 126,
	CMD_NO_FND_ERR = 127,
	STOP_PROGRAM = 128,
	CTRL_C = 130,
	SYNTAX_ERR = 258,
};

/* minishell.c */
void		handle_ctrlc(int signo);
int			path_is_directory(const char *path);

/* get_readline.c */
int			get_readline(char **line, t_env_list *env_list_head);

/* error_handling.c */
int			err_handler(t_list *list, int to_free, char *err_msg,
				int err_num);

/* minishell_utils_2.c */
char		*ft_strjoin_2(char *s1, char *s2);
void		free_list_cmd(t_list *list);
int			find_path(t_prompt **prompt);
int			is_relative_or_absolute(char *path);
int			check_binary_file_access(char *path);

/* split_tokens.c */
int			split_tokens(char ***tokens, char **s);

/* minishell_utils.c */
int			count_commands(char *argv[]);

/* parser.c */
int			parser(t_prompt **prompt, char **tokens);
char		*create_error_message(char *token, int err_number);

/* parser_2.c */
int			insert_cmd(t_list **curr);
int			count_words_in_cmd(char **tokens);
char		*remove_quotes(char *token);
int			sizeof_str(char *token);

/* redirections.c */
int			redirects_i_o(t_list *curr, int i, char **tokens);

/* executor.c */
int			executor(t_prompt **prompt);

/* executor_2.c */
int			close_pipes(t_list *list);
int			create_full_path(t_prompt **prompt);
int			env_list_to_array(t_prompt *prompt, char ***env);

/* executor_3.c */
void		close_input(t_prompt **prompt, t_list *curr);
void		close_output(t_prompt **prompt, t_list *curr);

/* ms_expander.c */
int			expand_array(char **arry, t_env_list *env_list);

/* ms_expander_2.c */
int			is_stop_sign(char c);
int			is_valid_variable(char *str, int i);
char		*ft_quote(char *str);
char		*expand_var(int a, int b, char *str, t_env_list *env_list_head);

/* ms_builtins.c */
int			execute_builtin(t_list *curr, t_env_list *env_list, int ret_val);
int			ft_echo(t_list *c);

/* ms_builtins_2.c */
int			ft_env(t_list *curr, t_env_list *env_list);
int			ft_export(t_list *curr, t_env_list *env_list);

/* ms_builtins_3.c */
int			ft_unset(t_list *s_list, t_env_list *env_list);
int			ft_echo(t_list *curr);

/* ms_builtins_4.c */
int			ft_exit(t_list *curr);
int			ft_pwd(t_list *curr);

/* ms_builtins_5.c */
int			ft_cd(t_list *curr, t_env_list *env_list);

/* ms_env.c */
t_env_list	*cpy_envp_to_env_list(char **envp);
char		*get_env_val(struct s_env_list *head, char *key);
int			free_env_list(t_env_list *head);

/* ms_env_2.c */
int			set_env_val(struct s_env_list *head, char *val);
int			checkvar(char *val);
char		*getkey(char *value);

/* here_doc.c */
int			get_here_doc_fd(char *delimiter);

/* check_tokens.c */
int			check_tokens(char **tokens);

/* ms_signals.c */
void		handle_ctrlc_outside_rl(int signo);
void		handle_ctrlc_inside_rl(int signo);
void		handle_ctrlc_inside_heredoc(int signo);

/* ms_signals.c */
int			modify_signals(void);
int			modify_signals2(void);
int			modify_signals3(void);
int			modify_sigquit(void);

#endif
