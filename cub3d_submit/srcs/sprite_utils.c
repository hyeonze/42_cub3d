/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <    @student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:22:53 by                   #+#    #+#             */
/*   Updated: 2021/02/16 23:15:03 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_max_line_size(t_list *lst)
{
	int		max;
	int		size;

	max = 0;
	while (lst)
	{
		size = ft_strlen((char *)lst->content);
		if (size > max)
			max = size;
		lst = lst->next;
	}
	return (max);
}

void	sort(t_info *info)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < info->num_sprite)
	{
		j = 0;
		while (j < info->num_sprite - 1)
		{
			if (info->sprite[j].distance < info->sprite[j + 1].distance)
			{
				temp = info->sprite[j + 1];
				info->sprite[j + 1] = info->sprite[j];
				info->sprite[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int		set_pos_sprite(t_info *info, int i, int x, int y)
{
	info->sprite[i].x = 0.5f + x;
	info->sprite[i].y = 0.5f + y;
	return (1);
}

int		set_sprite(t_info *info)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	if (!(info->sprite =\
			(t_sprite *)malloc(sizeof(t_sprite) * info->num_sprite)))
		return (exit_error(info));
	while (y < info->map_height)
	{
		x = 0;
		while (x < info->map_width)
		{
			if (info->map[y][x] == '2')
			{
				set_pos_sprite(info, i, x, y);
				i++;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int		has_two_comma(char *line)
{
	int i;
	int number_of_comma;

	i = 0;
	number_of_comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			number_of_comma++;
		i++;
	}
	if (number_of_comma == 2)
		return (1);
	return (0);
}
