# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_strlcat(char *dest, char *src, int len)
{
	int	i;
	int	j;

	if (!dest)
		return ;
	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && j < len)
		dest[i++] = src[j++];
	// printf("strlcat_test : [%s], i:%d\n", src, i);
}

void	*ft_memset(void *dest, int c, int len)
{
	int	i;

	i = 0;
	while (i < len)
		((unsigned char *)dest)[i++] = (unsigned char)c;
	return (dest);
}

void	*ft_calloc(int size, int len)
{
	void	*res;

	res = (void *)malloc(size * len);
	if (!res)
		return (NULL);
	res = ft_memset(res, 0, len);
	return (res);
}

int	ft_search_end(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_line(char **line)
{
	int	len;

	if (!line)
		return ;
	len = ft_search_end(*line);
	if (len == -1)
		(*line)[ft_strlen(*line)] = 0;
	else
		(*line)[len + 1] = 0;
}

void	ft_reste(char *buffer)
{
	int	i;
	int	j;

	i = ft_search_end(buffer) + 1;
	j = 0;
	if (i == -1)
		return (ft_memset(buffer, 0, 32), (void)0);
	while (buffer[i])
		buffer[j] = buffer[i++];
	while(buffer[j])
		buffer[j++] = 0;
}

char	*get_next_line(int fd)
{
	static char	buffer[32];
	char		*line;
	int			lu;

	if (fd < 0 || read(fd, NULL, 0) < 0 || 32 < 1)
		return (NULL);
	lu = 32;
	line = (char *)ft_calloc(sizeof(char), 10096);
	// printf("line = [%s] && buffer = [%s]\n", line, buffer);
	if (!line)
		return (NULL);
	ft_strlcat(line, buffer, 32);
	while (lu == 32 && ft_search_end(line) == -1)
	{
		lu = read(fd, buffer, 32);
		if (lu < 0)
			return (free(line), NULL);
		// printf("buffer:{%s} && line:[%s] && lu = %d\n", buffer, line, lu);
		buffer[lu] = 0;
		ft_strlcat(line, buffer, 32);
	}
	ft_line(&line);
	ft_reste(buffer);
	// printf("reste = [%s]\n", buffer);
	if (!ft_strlen(line))
		return (free(line), NULL);
	return (line);
}

char *get_next_line_test(int fd) 
{
    char *s = malloc(10000), *c = s;
    while (read(fd, c, 1) > 0 && *c++ != '\n');
    return c > s ? (*c = 0, s) : (free(s), NULL);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
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
