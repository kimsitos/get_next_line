/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stcozaci <stcozaci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:04:05 by stcozaci          #+#    #+#             */
/*   Updated: 2025/11/04 11:56:49 by stcozaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*get_line(int fd, char *line)
{
	char		*buffer;
	ssize_t		buffer_result;
	char		*temp_line;

	buffer_result = 1;
	if (fd == -1)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (buffer_result > 0)
	{
		buffer_result = read (fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';
		temp_line = line;
		line = ft_strjoin(temp_line, buffer);
		free(temp_line);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
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
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (0);
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
	char		*line;

	if (!rest)
		rest = ft_strdup("");
	rest = get_line(fd, rest);
	line = fill_line(rest);
	return (line);
}


#include <fcntl.h>

int main(void)
{
	int fd = open("texto.txt", O_RDONLY);
	char *linea;

	while ((linea = get_next_line(fd)) != NULL)
	{
		printf("Línea: %s", linea);
		free(linea);
	}

	close(fd);
	return (0);
}