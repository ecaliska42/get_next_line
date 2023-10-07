/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:29:06 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/07 16:08:22 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*line;
	char		*temp;
	int			alr_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	if (!str)
		str = ft_strdup("");
	while (has_next_line(str) == -1)
	{
		alr_read = read(fd, line, BUFFER_SIZE);
		if (alr_read <= 0)
			break ;
		line[alr_read] = '\0';
		str = ft_strjoin(str, line);
		if (!str)
			return (free (str), NULL);
	}
	free(line);
	line = NULL;
	if (alr_read < 0)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	if (str && has_next_line(str) != -1)
	{
		temp = get_one_line(str);
		str = new_str(str);
		return (temp);
	}
	else if (str && str[0] != '\0')
	{
		temp = ft_strdup(str);
		free(str);
		str = NULL;
		return (temp);
	}
	free(str);
	str = NULL;
	return (NULL);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	char	*str;
// 	int		fd;

// 	fd = open("subjext.txt", O_RDONLY);
// 	while ((str = get_next_line(fd))!= NULL)
// 	{
// 		printf("main function: \n\t%s\n", str);
// 		free (str);
// 	}
// 	//free (str);
// 	close (fd);
// 	return (0);
// }