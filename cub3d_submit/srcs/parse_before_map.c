/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_before_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:47:23 by hann              #+#    #+#             */
/*   Updated: 2021/02/16 23:18:42 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int		get_screen_size(t_info *info, char *line)
{
	char	**size;

	if (!(size = ft_split(line, ' ')))
		return (exit_error(info));
	if (!size || !size[0] || !size[1] || size[2])
		return (exit_error(info));
	if (!(ft_only_digit(size[0])) || !(ft_only_digit(size[1])))
		return (exit_error(info));
	info->width = ft_atoi(size[0]);
	info->height = ft_atoi(size[1]);
	ft_free_2d(size);
	if (!info->width || !info->height)
		return (exit_error(info));
	return (1);
}

int		get_texture(t_info *info, char *line, char *direction)
{
	if (direction[0] == 'N' && direction[1] == 'O'\
		&& info->north_texture_path == NULL)
		info->north_texture_path = ft_strdup(line);
	else if (direction[0] == 'S' && direction[1] == 'O'\
		&& info->south_texture_path == NULL)
		info->south_texture_path = ft_strdup(line);
	else if (direction[0] == 'W' && direction[1] == 'E'\
		&& info->west_texture_path == NULL)
		info->west_texture_path = ft_strdup(line);
	else if (direction[0] == 'E' && direction[1] == 'A'\
		&& info->east_texture_path == NULL)
		info->east_texture_path = ft_strdup(line);
	else if (direction[0] == 'S' && direction[1] == '\0'\
		&& info->sprite_texture_path == NULL)
		info->sprite_texture_path = ft_strdup(line);
	else
		return (exit_error(info));
	return (1);
}

int		get_color(t_info *info, char *line, int direction)
{
	char	**rgb;
	int		color;
	int		i;

	if (has_two_comma(line) != 1 || has_many_digit(line) != 1)
		return (exit_error(info));
	if (!(rgb = ft_split(line, ',')))
		return (exit_error(info));
	if ((!rgb || !rgb[0] || !rgb[1] || !rgb[2]) || (!(ft_only_digit(rgb[0]))\
		|| !(ft_only_digit(rgb[1])) || !(ft_only_digit(rgb[2]))))
		return (exit_error(info));
	color = 0;
	i = 0;
	while (rgb[i])
	{
		color *= 256;
		ft_atoi(rgb[i]) > 255 ? exit_error(info) : 0;
		color += ft_atoi(rgb[i++]);
	}
	color = color == 0 ? 1 : color;
	ft_free_2d(rgb);
	rgb = 0;
	info->floor_color = direction == 'F' ? color : info->floor_color;
	info->ceiling_color = direction == 'C' ? color : info->ceiling_color;
	return (1);
}

int		parse_line(t_info *i, char *l)
{
	if (ft_strncmp(l, "R ", 2) == 0 && ft_strncmp(l, "R  ", 3) != 0\
		&& i->width == 0 && i->height == 0)
		return (get_screen_size(i, l + 2));
	else if (ft_strncmp(l, "NO ", 3) == 0 && ft_strncmp(l, "NO  ", 4) != 0)
		return (get_texture(i, l + 3, "NO"));
	else if (ft_strncmp(l, "SO ", 3) == 0 && ft_strncmp(l, "SO  ", 4) != 0)
		return (get_texture(i, l + 3, "SO"));
	else if (ft_strncmp(l, "WE ", 3) == 0 && ft_strncmp(l, "WE  ", 4) != 0)
		return (get_texture(i, l + 3, "WE"));
	else if (ft_strncmp(l, "EA ", 3) == 0 && ft_strncmp(l, "EA  ", 4) != 0)
		return (get_texture(i, l + 3, "EA"));
	else if (ft_strncmp(l, "S ", 2) == 0 && ft_strncmp(l, "S  ", 3) != 0)
		return (get_texture(i, l + 2, "S"));
	else if (ft_strncmp(l, "F ", 2) == 0 && ft_strncmp(l, "F  ", 3) != 0\
		&& i->floor_color == 0)
		return (get_color(i, l + 2, 'F'));
	else if (ft_strncmp(l, "C ", 2) == 0 && ft_strncmp(l, "C  ", 3) != 0\
		&& i->ceiling_color == 0)
		return (get_color(i, l + 2, 'C'));
	else if (l[0] == '\0')
		return (1);
	return (0);
}

int		parse_cub(t_info *info, char *path)
{
	char	*line;
	int		ret;

	init_info(info);
	info->fd = open(path, O_RDONLY);
	while (get_next_line(info->fd, &line) > 0)
	{
		if ((ret = parse_line(info, line)) == -1)
			return (exit_error(info));
		if (ret == 0)
			break ;
		free(line);
	}
	if (!read_map(info, line))
		return (exit_error(info));
	if (!check_init(info))
		return (exit_error(info));
	if (!set_sprite(info))
		return (exit_error(info));
	return (1);
}
