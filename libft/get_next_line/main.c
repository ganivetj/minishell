#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char *get_next_line(int fd);

int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*ptr;

	if (argc < 2)
	{
		printf("No args received.\n");
		return (0);
	}
		fd = open(argv[1], O_RDONLY);
	
	i = 0;
	while (1)
	{	
		ptr = get_next_line(fd);
		if (ptr != 0)
		{
			printf("%-5d%s", i + 1, ptr);
		free(ptr);
		}
		else
		{
			printf("EOF\n");
			break;
		}
		++i;
	}
	return(0);
}
