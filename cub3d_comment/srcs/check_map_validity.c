/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                  >                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:23:35 by                   #+#    #+#             */
/*   Updated: 2021/02/08 12:36:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_left(t_info *info, int i, int j)
{
	while (info->map[i][j] == ' ')
		j++;
	if (info->map[i][j] != '1')
		return (exit_error(info));
	return (1);
}

int	check_map_top(t_info *info)
{
	int	i;

	i = 0;
	// ' '나 '1'이 아닌 것이 들어오면 에러처리
	while (i < (int)ft_strlen(info->map[0]))
	{
		if (!(info->map[0][i] == ' ' || info->map[0][i] == '1'))
			return (exit_error(info));
		i++;
	}
	return (1);
}

int	check_map_right(t_info *info, int i, int j)
{
	if (info->map[i][j - 1] != '1')
		return (exit_error(info));
	return (1);
}

int	check_map_bottom(t_info *info, int i)
{
	int	j;

	j = 0;
	while (j < (int)ft_strlen(info->map[i]))
	{
		if (!(info->map[i][j] == ' ' || info->map[i][j] == '1'))
			return (exit_error(info));
		j++;
	}
	return (1);
}

int	check_map_middle(t_info *info, int i, int j)
{
	// 첫줄이나 마지막줄이 아닌 경우
	if (i > 0 && i < info->map_height - 1)
	{
		// 아래나 위가 공백인데, 공백이나 1아닌게 들어올 경우 에러처리
		if (info->map[i - 1][j] == ' ' || info->map[i + 1][j] == ' ')
			if (info->map[i][j] != ' ' && info->map[i][j] != '1')
				return (exit_error(info));
	}
	// 좌우 끝줄이 아닌 경우
	if (j > 0 && j < info->map_width)
	{
		// 좌나 우가 공백인데, 공백이나 1아닌게 들어올 경우 에러처리
		if (info->map[i][j - 1] == ' ' || info->map[i][j + 1] == ' ')
			if (info->map[i][j] != ' ' && info->map[i][j] != '1')
				return (exit_error(info));
	}
	return (1);
}
