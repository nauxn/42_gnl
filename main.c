#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;
	int		text1_active;
	int		text2_active;

	line1 = NULL;
	line2 = NULL;
	if (argc == 2)
	{
		fd1 = open(argv[1], O_RDONLY);
		if (fd1 < 0)
		{
			printf("Error opening test files.\n");
			return (1);
		}
		while ((line1 = get_next_line(fd1)) != NULL)
		{
			printf("%s", line1);
			free(line1);
		}
		close(fd1);
	}
	else if (argc == 3)
	{
		fd1 = open(argv[1], O_RDONLY);
		fd2 = open(argv[2], O_RDONLY);
		if (fd1 < 0 || fd2 < 0)
		{
			printf("Error opening test files.\n");
			return (1);
		}
		text1_active = 1;
		text2_active = 1;
		while (text1_active || text2_active)
		{
			if (text1_active)
			{
				line1 = get_next_line(fd1);
				if (line1)
				{
					printf("[FD %d]: %s", fd1, line1);
					free(line1);
				}
				else
					text1_active = 0;
			}
			if (text2_active)
			{
				line2 = get_next_line(fd2);
				if (line2)
				{
					printf("[FD %d]: %s", fd2, line2);
					free(line2);
				}
				else
					text2_active = 0;
			}
		}
		close(fd1);
		close(fd2);
	}
	return (0);
}
