/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:29:06 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/03 17:50:49 by ecaliska         ###   ########.fr       */
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
        if (line[i] == '\n' || line[i] == '\0')
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
    //printf("i = %d\n", i);
    new_string[++i] = '\n';
    new_string[++i] = '\0';
    return (new_string);
}
// char    str_trim(char *str, char *temp)
// {
//     int i;

//     i = 0;
//     while (temp[i] == str[i])
//     {
//         str++;
//         i++;
//     }
//     return (*str);
// }

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

    line = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (!line)
        return (NULL);
    if (count == 0)
        str = ft_strdup ("");
    printf("teststring = %s\n", str);
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (read(fd, line, BUFFER_SIZE) != 0)
    {
        count++;
        str = ft_strjoin(str, line);
        if (has_next_line(str) == -1)
            continue;
        else
        {
            printf("str = %s\n", str);
            temp = get_one_line(str);
            str = ft_strchr(str, '\n');
            printf("temp = %s\n", temp);
            printf("new str = %s\n", str);
            //break;
            return (temp);
        }
    }
    return (temp);
}

int main(void)
{
    char *str;
    int fd = open("subjext.txt", O_RDONLY);
    while ((str = get_next_line(fd)) != NULL)
    {
        printf("main function: %s\n\n\n", str);
        free (str);
    }
    close (fd);
    //printf("%s", get_next_line(fd));
    return (0);
}