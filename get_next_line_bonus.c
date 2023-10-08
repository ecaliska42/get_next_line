/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:58:12 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/08 17:15:56 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	has_next_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_one_line(char *str)
{
	int		i;
	char	*new_string;

	i = 0;
	while (str[i] != '\n' && str[i])
	{
		i++;
	}
	new_string = (char *)malloc(sizeof(char) * i + 2);
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

static char	*freeing(char **str)
{
	free (*str);
	*str = NULL;
	return (NULL);
}

static char	*ft_temptest(char **str)
{
	char	*temp;

	temp = NULL;
	if (has_next_line(*str) != -1)
	{
		temp = get_one_line(*str);
		*str = new_str(*str);
		return (temp);
	}
	else if ((*str)[0] != '\0')
	{
		temp = ft_strdup(*str);
		free (*str);
		*str = NULL;
		return (temp);
	}
	free (*str);
	*str = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*str[2048];
	char		*line;
	int			alr_read;

	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (free (line), NULL);
	if (!str[fd])
		str[fd] = ft_strdup("");
	while (has_next_line(str[fd]) == -1)
	{
		alr_read = read(fd, line, BUFFER_SIZE);
		if (alr_read <= 0)
			break ;
		line[alr_read] = '\0';
		str[fd] = ft_strjoin(str[fd], line);
		if (!str[fd])
			return (freeing (&line));
	}
	free(line);
	if (alr_read < 0)
		return (freeing(&str[fd]));
	if (str[fd])
		return (ft_temptest(&str[fd]));
	return (freeing(&str[fd]));
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	char	*str;
// 	int		fd;

// 	fd = open("subjext.txt", O_RDONLY);
// 	while ((str = get_next_line(fd)) != NULL)
// 	{
// 		printf("main function: \n\t%s\n", str);
// 		free (str);
// 	}
// 	close (fd);
// 	return (0);
// }
