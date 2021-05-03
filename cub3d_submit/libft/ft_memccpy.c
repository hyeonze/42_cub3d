/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <    @student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:15:24 by                   #+#    #+#             */
/*   Updated: 2021/02/08 12:43:53 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	size_t i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < len)
	{
		((t_uchar *)dst)[i] = ((t_uchar *)src)[i];
		if (((t_uchar *)dst)[i] == (t_uchar)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
