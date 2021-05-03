/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <    @student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:15:24 by                   #+#    #+#             */
/*   Updated: 2021/02/08 12:46:34 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	src_len;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	index = 0;
	if (size == 0)
		return (src_len);
	while (index + 1 < size && src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (src_len);
}
