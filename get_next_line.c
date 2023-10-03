/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:29:06 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/03 19:59:49 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static int has_next_line(const char *line)
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

static char *get_one_line(const char *str)
{
    int     i;
    char    *new_string;

    i = 0;
    while (str[i] != '\n')
    {
        i++;
    }
    new_string = (char *)malloc (sizeof (char) * i + 2);
    i = 0;
    while (str[i] != '\n')
    {
        new_string[i] = str[i];
        i++;
    }
    new_string[++i] = '\n';
    new_string[++i] = '\0';
    return (new_string);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char *)++s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

char    *get_next_line(int fd)
{
    static char *str = NULL;
    char        *line;
    char        *temp = NULL;
    static int  count = 0;
    int         alr_read;

    line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!line || fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (count++ == 0)
        str = ft_strdup ("");
    while ((alr_read = read(fd, line, BUFFER_SIZE)) != 0)
    {
        line[alr_read] = '\0';
        str = ft_strjoin(str, line);
        if (has_next_line(str) == -1)
            continue;
        else
        {
            temp = get_one_line(str);
            str = ft_strchr(str, '\n');
            return (temp);
        }
    }
    if (alr_read == 0 && str)
        return (ft_strdup(str));
    return (NULL);
}

int main(void)
{
    char *str;
    int i = 0;
    int fd = open("subjext.txt", O_RDONLY);
    while (i++ < 4)
    {
        str = get_next_line(fd);
        printf("main function: \n\t%s\n", str);
        free (str);
    }
    close (fd);
    return (0);
}