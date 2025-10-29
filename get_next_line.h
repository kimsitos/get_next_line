/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stcozaci <stcozaci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:04:08 by stcozaci          #+#    #+#             */
/*   Updated: 2025/10/29 18:04:19 by stcozaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 7
# endif

char	*get_next_line(int fd);

//gnl_utils.c
int		ft_strchr(const char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif