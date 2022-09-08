#include <stdio.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*ret;
	int			lu;

	if (fd < 0)
		return (NULL);
	lu = 1;
	while (lu == BUFFER_SIZE && *line)
	{
		lu = read(fd, buffer, BUFFER_SIZE);
		if (!lu)
			break ;
	}
}