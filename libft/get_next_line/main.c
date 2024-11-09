#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char *get_next_line(int fd);

int	main(int argc, char **argv)
{
	int		i;
	int		fd;
//	int		fd2;
	char	*ptr;
//	int		j;

//	printf("argc : %i\n", argc);
	if (argc < 2)
	{
		printf("No args received.\n");
		return (0);
	}
		fd = open(argv[1], O_RDONLY);
	//	fd2 = open(argv[2], O_RDONLY);
	//	printf("fd %d is open\n", fd);
	
	i = 0;
	while (1)
	{	
//		printf("LOOP %d\n", i);
		ptr = get_next_line(fd);
//		printf("main.c : gnl returned %p\n", ptr);
		if (ptr != 0)
		{
			printf("%-5d%s", i + 1, ptr);
		//	j = 0;
		//	while(ptr[j] != '\n')
		//	{		
		//		printf("%c", ptr[j]);
		//		++j;
		//	}
//		printf ("\n");	
		free(ptr);
		}
		else
		{
			printf("EOF\n");
			
			break;
		}
//		if (ptr[j] == '\0')
//			break;
		++i;
	}


	return(0);
}
