/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stcozaci <stcozaci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:04:05 by stcozaci          #+#    #+#             */
/*   Updated: 2025/11/04 16:27:03 by stcozaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*get_line(int fd, char *line, char *buffer)
{
	ssize_t		buffer_result;
	char		*temp_line;
	int i = 0;

	buffer_result = 1;

	
	while (buffer_result > 0)
	{
		buffer_result = read (fd, buffer, BUFFER_SIZE);
		if (buffer_result == -1)
		{
			printf("(get_line:33)read error\n");
			return (NULL);
		}
		if (buffer_result == 0)
		{
			printf("(get_line:35)all archive read\n");
			break ;
		}
		temp_line = line;
		printf("(get_line:39)===Joining for %d %s to %s===\n", i++, buffer, line);
		line = ft_strjoin(temp_line, buffer);
		free(temp_line);
		if (ft_strchr(buffer, '\n'))
		{
			printf ("(get_line:44)\\n found in buffer\n");
			break ;
		}
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
	if (!rest[i])
	{
		printf("(fill_line:64)end of rest, sorry\n");
		return (NULL);
	}
	line = malloc((i + 1) * sizeof(char));
	if (!line)
	{
		printf("(fill_line:70)line error creating\n");
		return (NULL);
	}
	printf("(fill_line:73)==Copyint string until \\n==\n");
	while (i > j)
	{
		printf("	(fill_line:76)char number %zu for line copyed\n", j);
		line[j] = rest[j];
		j++;
	}
	line[j] = '\0';
	printf("(fill_line:81)--=Line made it succesfuly=--\n");
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*rest;
	char		*line;

	if (fd == -1 || BUFFER_SIZE < 0)
	{
		printf("(get_next_line:93)null file descriptor\n");
		return (NULL);
	}
	if (!rest)
	{
		printf("(get_next_line:98)no rest, creating rest\n");
		rest = ft_strdup("");
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		printf("(get_next_line:104)buffer error creating\n");
		return (0);
	}
	line = get_line(fd, rest, buffer);
	rest = fill_line(line);
	if (!rest)
		return (NULL);
	line = ft_substr(rest, ft_strlen(rest), ft_strlen(line) - ft_strlen(rest));
	return (rest);
}


#include <fcntl.h>

int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	char *linea;
	int i = 0;

	// linea = get_next_line(fd);
	// free (linea);
	// linea = get_next_line(fd);
	while ((linea = get_next_line(fd)) != NULL && i++ < 4)
	{
		printf ("##RESULT##%s\n", linea);
		free(linea);
	}

	close(fd);
	return (0);
}