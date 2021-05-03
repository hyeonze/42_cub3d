/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <    @student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:24:16 by                   #+#    #+#             */
/*   Updated: 2021/02/08 12:36:36 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_floor_ceiling(t_info *info)
{
	int y;
	int x;

	y = -1;
	while (++y < info->height)
	{
		x = -1;
		while (++x < info->width)
		{
			if (y > info->height / 2)
				info->buf[y][x] = info->floor_color;
			else
				info->buf[y][x] = info->ceiling_color;
		}
	}
}
