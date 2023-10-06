/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:29:06 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/06 20:58:59 by ecaliska         ###   ########.fr       */
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
	//printf("\nGET_ONE_LINE=%i\n", i);
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
    //free ((char *)str);
    return (new_string);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	char	ch;

// 	ch = c;
// 	while (*s != '\0')
// 	{
// 		if (*s == ch)
// 			return ((char *)s);
//         s++;
// 	}
// 	if (ch == '\0')
// 		return ((char *)s);
// 	return (NULL);
// }
char    *new_str(char *str)
{
    char    *temp;
    int     i;
    int     j;

    i = 0;
    j = 0;
    // while (str[i] != '\0')
    //     i++;
    i = ft_strlen(str);
    while (str[j] != '\n')
        j++;
    if (str[j] == '\n')
        j+=1;
    temp = (char *)malloc ((sizeof(char) * (i - j)));
	//printf("\nNEW_STR=%i\n", i);
    if (!temp)
        return (NULL);
    i = 0;
    while (str[j])
    {
        temp[i] = str[j];
        j++;
        i++;
    }
    temp[i] = '\0';
    free (str);
    return (temp);
}

char    *get_next_line(int fd)
{
    static char *str = NULL;
    char        *line;
    char        *temp = NULL;
    int         alr_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	//printf("\nGET_NEXT_LINE=%i\n", fd);
    if (!line)
        return (NULL);
    if (!str)
        str = ft_strdup("");
    while (has_next_line(str) == -1 &&(alr_read = read(fd, line, BUFFER_SIZE)) > 0)
    {
        line[alr_read] = '\0';
        str = ft_strjoin(str, line);
        //free (line);
    }
    free (line);
    // if (alr_read < 0)
    // {
    //     free(str);
    //     return (NULL);
    // }
    if (str && str[0] == '\0')
    {
        free (str);
        str = NULL;
        return (str);
    }
    if(str && has_next_line(str) != -1)
    {
        temp = get_one_line(str);
        str = new_str(str);
        return (temp);
    }
    if (str)
    {
        temp = ft_strdup(str);
        free (str);
        str = NULL;
        return (temp);
    }
    free (str);
    str = NULL;
    return (NULL);
}

// int main(void)
// {
//     char *str;
//     int fd = open("subjext.txt", O_RDONLY);
//     //str = get_next_line(fd);
//     //printf("Line: %s", str);

//     while ((str = get_next_line(fd))!= NULL)
//     {
//         //str = get_next_line(fd);
//         printf("main function: \n\t%s\n", str);
//         free (str);
//     }
//     //free (str);
//     close (fd);
//     return (0);
// }