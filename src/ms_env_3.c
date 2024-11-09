#include "minishell.h"

int	set_env_val_2(struct s_env_list *curr, char *val, char *search_key,
	char *curr_env_key)
{
	free(curr_env_key);
	free(curr->value);
	curr->value = ft_strdup(val);
	free(search_key);
	return (0);
}