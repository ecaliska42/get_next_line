/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:29:06 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/07 00:33:38 by ecaliska         ###   ########.fr       */
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

	temp = NULL;
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
	}
	free(line);
	if (alr_read < 0)
	{
		free(str);
		free(temp);
		str = NULL;
		temp = NULL;
		line = NULL;
		return (NULL);
	}
	if (str && str[0] == '\0')
	{
		free(str);
		str = NULL;
		return (str);
	}
	if (str && has_next_line(str) != -1)
	{
		temp = get_one_line(str);
		str = new_str(str);
		return (temp);
	}
	if (str)
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

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*str;
	int		fd;

	fd = open("subjext.txt", O_RDONLY);
	while ((str = get_next_line(fd))!= NULL)
	{
		printf("main function: \n\t%s\n", str);
		free (str);
	}
	close (fd);
	return (0);
}