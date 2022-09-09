#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	char *str=malloc(99999999), *copy = str;
	while (read(fd, copy, 1) > 0 && *copy++ != '\n');
	return (copy > str) ? (*copy = 0, str) : (free(str), NULL);
}

// int	main(void)
// {
// 	char	*line;
// 	char	*path;
// 	int		i = 0;
// 	int		fd;

// 	path = "test.txt";
// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		return (printf("Error: Open failed\n"));
// 	line = get_next_line(fd);
// 	while (line || i < 1)
// 	{
// 		printf("line %d : {%s}\n", i++ + 1, line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (0);
// }