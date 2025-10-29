/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stcozaci <stcozaci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:04:05 by stcozaci          #+#    #+#             */
/*   Updated: 2025/10/29 18:04:54 by stcozaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	line = "";
	if (fd == -1)
		return (NULL);
	str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str)
		return (0);
	while (ft_strchr(line, '\n'))
	{
		read(fd, str, BUFFER_SIZE);
		line = ft_strjoin(str, line);
	}
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