/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                  >                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:55:12 by                   #+#    #+#             */
/*   Updated: 2021/02/08 12:40:01 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_error(t_info *info)
{
	ft_putstr("Error\n");
	if (info->fd)
		close(info->fd);
	exit(0);
	return (-1);
}

int		check_init(t_info *info)
{
	if (!info->width || !info->height || !info->map_width ||\
		!info->map_height || !info->north_texture_path ||\
		!info->south_texture_path || !info->west_texture_path ||\
		!info->east_texture_path || !info->sprite_texture_path ||\
		!info->floor_color || !info->ceiling_color)
		return (exit_error(info));
	return (1);
}

void	ft_free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int		is_dir(int c)
{
	if (c == 'N' || c == 'S' ||\
		c == 'E' || c == 'W')
		return (1);
	return (-1);
}

int		is_map_arg(int c)
{
	if (is_dir(c) == 1 || c == ' ' ||\
		(c >= '0' && c <= '2') ||\
		c == '\n' || c == '\0')
		return (1);
	return (-1);
}
