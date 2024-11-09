#include "libft.h"

void	ft_free_2d_void_array(void **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
	{
		free(array[i]);
		++i;
	}
	free(array);
}

void	ft_free_2d_int_array(int **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
	{
		free(array[i]);
		++i;
	}
	free(array);
}

void	ft_free_2d_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
	{
		free(array[i]);
		++i;
	}
	free(array);
}
