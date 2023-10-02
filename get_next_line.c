/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:29:06 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/02 16:31:29 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int has_next_line(const char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char    *get_next_line(int fd)
{
    static char *str = NULL;
    int     sz;
    char    *line;
    int     i;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    line = (char *)malloc(sizeof (char) * (BUFFER_SIZE + 1));
    if (!line)
        return (NULL);
    sz = read(fd, line, BUFFER_SIZE);
    i = has_next_line(line);
    if (i != -1)
    {
        ft_strjoin(str, line);
    }
    return (str);        
}

int main(void)
{
    char *str;
    int fd = open("subjext.txt", O_RDONLY);
    get_next_line(fd);
    return (0);
    while ((str = get_next_line(fd)) != NULL)
    {
        printf("%s", str);
        free (str);
    }
}