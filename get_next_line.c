/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:29:06 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/05 18:10:19 by ecaliska         ###   ########.fr       */
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
    while (str[i] != '\n' && str[i])
    {
        i++;
    }
    new_string = (char *)malloc (sizeof (char) * i + 2);
    if (!new_string)
        return (NULL);
    i = 0;
    while (str[i] != '\n' && str[i])
    {
        new_string[i] = str[i];
        i++;
    }
    new_string[i] = '\n';
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
			return ((char *)s);
        s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}
// char    *new_str(char *str)
// {
//     char    *temp;
//     int     i;
//     int     j;

//     i = 0;
//     j = 0;
//     //printf("GETSINTHEFUNCTION");
//     //printf("\nSTR=%s\n", str);
//     // while (str[i] != '\0')
//     //     i++;
//     i = ft_strlen(str);
//     //printf("\ni = %d\n", i);
//     while (str[j] != '\n')
//         j++;
//     if (str[j] == '\n')
//         j+=1;
//     //printf("\nj = %d\n", j);
//     temp = (char *)malloc ((sizeof(char) * (i - j)) + 100);
//     if (!temp)
//         return (NULL);
//     //printf("\nPASSES\n");
//     i = 0;
//     while (str[j])
//     {
//         temp[i] = str[j];
//         //printf("as\n");
//         j++;
//         i++;
//     }
//     temp[i] = '\0';
//     //printf("\nTEMP = %s\n", temp);
//     //free (str);
//     return (temp);
// }
char    *get_next_line(int fd)
{
    static char *str;
    char        *line;
    char        *temp = NULL;
    int         alr_read;

    line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!line || fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!str)
        str = ft_strdup("");
    while (has_next_line(str) == -1 &&(alr_read = read(fd, line, BUFFER_SIZE)) > 0)
    {
        line[alr_read] = '\0';
        //printf("\nHEREWHILE\n");
        str = ft_strjoin(str, line);
        //printf("\nSTRING=%s\n", str);
        //free (line);
    }
    //free (line);
    if (str && str[0] == '\0')
    {
        str = NULL;
        //printf("\nHERE1\n");
        return (NULL);
    }
    if(str && ft_strchr(str, '\n') != NULL)
    {
        temp = get_one_line(str);
        //printf("\nstr=%s\n", str);
        //printf("\nHERELINE\n");
        //printf("\ntemp=%s\n", temp);
        //str = ft_strchr(str, '\n');
        str = ft_strchr(str, '\n') + 1;
        //printf("\nNEWSTRING=%s\n", str);
        return (temp);
    }
    if (str)
    {
        temp = get_one_line(str);
        str = NULL;
        //free (str);
        return (temp);
    }
    //printf("\nHERE2\n");
    return (NULL);
}

int main(void)
{
    char *str;
    int i = 0;
    int fd = open("subjext.txt", O_RDONLY);
    //str = get_next_line(fd);
    //printf("Line: %s", str);

    while ((str = get_next_line(fd))!= NULL || i < 8)
    {
        //str = get_next_line(fd);
        printf("main function: \n\t%s\n", str);
        free (str);
        i++;
    }
    //free (str);
    close (fd);
    return (0);
}