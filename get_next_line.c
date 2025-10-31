/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stcozaci <stcozaci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:04:05 by stcozaci          #+#    #+#             */
/*   Updated: 2025/10/31 13:01:17 by stcozaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*line;
	ssize_t		buffer_result;

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
		line = ft_strjoin(line, buffer);
		printf("LINEA ACTUAL: %s\nBUFFER AÑADIDO: %s\n--------------\n", line, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (line);
}


#include <fcntl.h>

int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	char *str = get_next_line(fd);
	close (fd);
	printf ("RESULT: %s\n", str);
	free(str);
	return 0;
}