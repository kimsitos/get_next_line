/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stcozaci <stcozaci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:04:05 by stcozaci          #+#    #+#             */
/*   Updated: 2025/11/06 13:49:47 by stcozaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(int fd, char *line)
{
	ssize_t		buffer_result;
	char		*temp_line;
	char		*buffer;

	buffer_result = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (buffer_result > 0)
	{
		buffer_result = read (fd, buffer, BUFFER_SIZE);
		buffer[buffer_result] = '\0';
		if (buffer_result < 0)
			return (NULL);
		if (buffer_result == 0)
			break ;
		temp_line = line;
		line = ft_strjoin(temp_line, buffer);
		free(temp_line);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (line);
}

static char	*fill_line(char *rest)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	if (!rest || !rest[0])
		return (NULL);
	while (rest[i] != '\n' && rest[i])
		i++;
	if (rest[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i > j)
	{
		line[j] = rest[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*temp;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
	{
		free(rest);
		return (NULL);
	}
	if (!rest)
		rest = ft_strdup("");
	if (!ft_strchr(rest, '\n'))
		rest = get_line(fd, rest);
	line = fill_line(rest);
	if (!line)
	{
		return (NULL);
	}
	temp = rest;
	rest = ft_substr(temp, ft_strlen(line), ft_strlen(temp) - ft_strlen(line));
	free(temp);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main(void)
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	char *linea;
// 	int i = 1;
// 	while ((linea = get_next_line(fd)))
// 	{
// 		printf ("##RESULT NUMBER %d##%s", i, linea);
// 		free(linea);
// 		i++;
// 	}
// 	get_next_line(-1);
// 	close(fd);
// 	return (0);
// }
