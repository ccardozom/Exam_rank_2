#include "get_next_line_copy.h"
#include <stdio.h>
int get_next_line(char **line)
{
    static char *gnl;
    char buff[513], *temp, *temp2;
    int bt;

    if (!line)
        return (-1);
    while (ft_strchr(gnl, '\n') == NULL)
    {

    }
}