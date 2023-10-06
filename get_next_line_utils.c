/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:29:03 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/06 20:56:36 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include <stddef.h>
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1||!s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1)+ft_strlen(s2)) + 1);
	//printf("\nSTRJOIN=%i\n", i);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free ((char *)s1);
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;
	int		len;
	
	len = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	//printf("\nSTRDUP=%i\n", len);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}