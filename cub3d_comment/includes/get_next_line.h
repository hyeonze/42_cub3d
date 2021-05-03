/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <    @student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:39:09 by                   #+#    #+#             */
/*   Updated: 2021/02/08 12:40:43 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

char	*str_dup_cat(char *s1, char *s2);
int		get_line(char *lines, char **line, char *found_chr);
char	*read_lines(int fd, char **line, char *lines);
int		get_next_line(int fd, char **line);

#endif
