/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:15:24 by hann              #+#    #+#             */
/*   Updated: 2021/02/08 12:43:58 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (((t_uchar *)s)[i] == (t_uchar)c)
			return ((t_uchar *)s + i);
		i++;
	}
	return (NULL);
}
