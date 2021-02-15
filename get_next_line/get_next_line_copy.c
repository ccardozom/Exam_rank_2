#include "get_next_line_copy.h"

int get_next_line(char **line)
{
	char *join, buffer[1];
	int ret, index;

	if (!(*line = malloc(1)) || !line)
		return (-1);
	(*line)[0] = '\0';
	while ((ret = read(0, buffer, 1)) > 0)
	{
		if (buffer[0] == '\0' || buffer[0] == '\n')
			break;
		index = 0;
		while ((*line)[index])
			index++;
		if (!(join = malloc(index + 2)))
			return (-1);
		index = 0;
		while ((*line)[index] != '\0')
		{
			join[index] = (*line)[index];
			index++;
		}
		join[index++] = buffer[0];
		join[index++] = '\0';
		free(*line);
		*line = join;
	}
	return (ret);
}