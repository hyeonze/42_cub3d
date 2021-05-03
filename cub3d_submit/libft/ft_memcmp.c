/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                  >                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:15:24 by                   #+#    #+#             */
/*   Updated: 2021/02/08 12:44:01 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (!s1 && !s2)
		return (0);
	if (n <= 0)
		return (0);
	while (index + 1 < n)
	{
		if (((t_uchar *)s1)[index] != ((t_uchar *)s2)[index])
			return (((t_uchar *)s1)[index] - (((t_uchar *)s2)[index]));
		index++;
	}
	return (((t_uchar *)s1)[index] - ((t_uchar *)s2)[index]);
}
