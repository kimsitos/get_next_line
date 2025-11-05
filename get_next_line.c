/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stcozaci <stcozaci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:04:05 by stcozaci          #+#    #+#             */
/*   Updated: 2025/11/05 18:25:46 by stcozaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*get_line(int fd, char *line, char *buffer)
{
	ssize_t		buffer_result;
	char		*temp_line;

	buffer_result = 1;

	
	while (buffer_result > 0)
	{
		buffer_result = read (fd, buffer, BUFFER_SIZE);
		buffer[buffer_result] = '\0';
		if (buffer_result == -1)
			return (NULL);
		if (buffer_result == 0)
			break ;
		temp_line = line;
		line = ft_strjoin(temp_line, buffer);
		free(temp_line);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}

static char	*fill_line(char *rest)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	while (rest[i] != '\n' && rest[i])
		i++;
	if (!rest[i])
		return (NULL);
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
	char		*buffer;
	static char	*rest;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest)
		rest = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	if (!ft_strchr(rest, '\n'))
		rest = get_line(fd, rest, buffer);
	line = fill_line(rest);
	if (!line)
		return (NULL);
	rest = ft_substr(rest, ft_strlen(line) + 1, ft_strlen(rest) - ft_strlen(line));
	return (line);
}


#include <fcntl.h>

int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	char *linea;
	int i = 1;

	// linea = get_next_line(fd);
	// free (linea);
	// linea = get_next_line(fd);
	while ((linea = get_next_line(fd)))
	{
		printf ("##RESULT NUMBER %d##%s\n", i, linea);
		free(linea);
		i++;
	}

	close(fd);
	return (0);
}