*This project has been created as part of the 42 curriculum by nisim.*

# `get_next_line()`

## Description
This project requires building a function that reads from a file descriptor and returns one line at a time, based on the newline character (`'\n'`). The returned line must include the terminating '\n' character. The only exception is when the function reaches the `End Of File (EOF)` on a line that does not end with a newline. 

The function must read the file `BUFFER_SIZE` bytes at a time until a newline character is found. It must return the line immediately upon discovery, rather than reading the entire file in a single function call.

During compilation, the `BUFFER_SIZE` macro can be modified to change how many bytes are retrieved from the file descriptor at once. The function must work seamlessly with various buffer sizes, including extreme values like `1`, `9999`, and `100000`.

The project is divided into two parts:

1. Mandatory Part: 
In the function, a local buffer is created to store `BUFFER_SIZE` bytes of characters from the file descriptor. These characters are continuously appended to a static string variable. Static variables are used because they persist across function calls, unlike standard local variables that are destroyed upon function exit. A single line, up to and including the newline character, is extracted from this static string and assigned to the line variable, which is then returned. The extracted line is removed from the static string, and the remaining characters are shifted forward so they are ready for the next call to `get_next_line()`.

2. Bonus Part😈: 
The bonus part extends `get_next_line()` to manage multiple file descriptors simultaneously without losing track of the remaining text in any of the files. A linked list is utilized to handle multiple file descriptors. Each node in the list stores a specific file descriptor, its corresponding remaining string, and a pointer to the next node. Whenever the function is called for a specific file descriptor, it locates or creates the corresponding node. It then updates the remaining string exactly like the mandatory part, ensuring old memory is freed before allocating space for the updated remaining string.

## Instruction
No installation is required to test the function.

With a main file, the function may be compiled using `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o output`

For testing the bonus function, the compilation will be done with `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *bonus.c main.c -o output`

***Note***
1. *You may adjust the BUFFER_SIZE to any integer to test the function.*
2. *Flags may be added to the compilation line to check for leaks. (To check with Address Sanitizer, simply add the `-fsanitize=address` flag, as for valgrind, simply add the `-g` flag in the compilation code, and then use `valgrind --leak-check=full --show-leak-kinds=all ./output <filename> ...` to check for heap leaks.)*
3. *An example of the main file is included below after the `Resources` section.*

## Resources
1. Google Gemini for debugging process. Structural frameworks on algorithms and clarifications on data type/parameter were referenced to guide the implementation of functions. 
2. Apart from own main file, a tester from github was also used to examine (URL: `https://github.com/Sfabi28/gnl_tester.git`) 

```
Main file:

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
```
