NAME		= minishell

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address -I$(LIBFT_DIR) -I/usr/local/opt/readline/include

LDFLAGS		= -L/usr/local/opt/readline/lib -lreadline

RM			= rm -f

SRC			= src/minishell.c \
			  src/minishell_utils.c \
			  src/minishell_utils_2.c \
			  src/minishell_utils_3.c \
			  src/split_tokens.c \
			  src/parser.c \
			  src/parser_2.c \
			  src/redirections.c \
			  src/executor.c \
			  src/executor_2.c \
			  src/executor_3.c \
			  src/ms_expander.c \
			  src/ms_expander_2.c \
			  src/error_handling.c \
			  src/get_readline.c \
			  src/ms_builtins.c \
			  src/ms_builtins_2.c \
			  src/ms_builtins_3.c \
			  src/ms_builtins_4.c \
			  src/ms_builtins_5.c \
			  src/ms_env.c \
			  src/ms_env_2.c \
			  src/ms_env_3.c \
			  src/here_doc.c \
			  src/check_tokens.c \
			  src/ms_signals.c \
			  src/ms_signals_2.c

OBJ			= $(SRC:.c=.o)

%.o: %.c src/minishell.h
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

all:		$(NAME)

clean:
			$(RM) $(OBJ)
			$(MAKE) clean -C $(LIBFT_DIR)

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) fclean -C $(LIBFT_DIR)

re:			fclean all

.PHONY:		all clean fclean re
