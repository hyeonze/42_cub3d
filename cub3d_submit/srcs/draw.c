/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:13:06 by hann              #+#    #+#             */
/*   Updated: 2021/02/18 17:20:12 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			info->img.data[info->width * y + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int		has_many_digit(char *line)
{
	int i;
	int number_of_comma;
	int number_of_number;

	i = 0;
	number_of_comma = 0;
	number_of_number = 0;
	while (number_of_comma < 2)
	{
		if (line[i] == ',')
			number_of_comma++;
		i++;
	}
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 1)
			number_of_number++;
		i++;
	}
	if (number_of_number > 3)
		return (0);
	return (1);
}

int		check_name(char *cub)
{
	int i;

	i = 0;
	while (cub[i])
		i++;
	i--;
	if (cub[i] != 'b')
		return (0);
	i--;
	if (cub[i] != 'u')
		return (0);
	i--;
	if (cub[i] != 'c')
		return (0);
	i--;
	if (cub[i] != '.')
		return (0);
	return (1);
}