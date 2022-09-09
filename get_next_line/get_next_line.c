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


int	main(void)
{
	char	**ret;
	char	**ret2;
	char	*line;
	int		fd;
	int		i;
	char	*path;

	path = "gnlTester/files/41_with_nl";
	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("\e[31mError: open failed\e[0m\n"));
	line = get_next_line(fd);
	ret = ft_calloc(sizeof(char *), 100);
	ret2 = ft_calloc(sizeof(char *), 100);
	while (line)
	{
		if (!ret)
			break ;
		ret[i++] = line;
		line = get_next_line(fd);
	}
	i = 0;
	close(fd);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("\e[31mError: open failed\e[0m\n"));
	line = get_next_line_test(fd);
	while (line)
	{
		if (!ret2)
			break ;
		ret2[i++] = line;
		line = get_next_line_test(fd);
	}
	i = 0;
	while (ret2[i] || ret[i])
	{
		printf("my_ret = {%s}\ncorrec = {%s}\n", ret[i], ret2[i]);
		if (ft_strcmp(ret[i], ret2[i]))
			printf("KO\n");
		else
			printf("OK\n");
		free(ret[i]);
		free(ret2[i++]);
	}
	return (close(fd), free(ret), free(ret2), 0);
}
