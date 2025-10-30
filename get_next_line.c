/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stcozaci <stcozaci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:04:05 by stcozaci          #+#    #+#             */
/*   Updated: 2025/10/30 15:04:35 by stcozaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	//char		*temp_line;
	ssize_t		buffer_result;

	line = "";
	buffer_result = 1;
	if (fd == -1)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (buffer_result > 0)
	{
		buffer_result = read (fd, buffer, BUFFER_SIZE);
		
		//temp_line = line;
		line = ft_strjoin(line, buffer);
		//free(temp_line);
		if (ft_strchr(buffer, '\n'))
			break ;
		free(buffer);
	}
	free(buffer);
	return (line);
}


#include <fcntl.h>

int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	char *str = get_next_line(fd);
	printf ("RESULT: %s\n", str);
	free(str);
	close (fd);
	return 0;
}