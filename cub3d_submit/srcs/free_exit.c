/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                  >                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:14:32 by                   #+#    #+#             */
/*   Updated: 2021/02/08 12:34:31 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit(int ret)
{
	exit(ret);
	return (ret);
}

void	ft_free(void *s)
{
	free(s);
	s = 0;
}

int		free_cub(t_info *info)
{
	if (info->img.img)
		mlx_destroy_image(info->mlx, info->img.img);
	if (info->sprite)
		ft_free(info->sprite);
	if (info->buf)
		ft_free_2d((void *)info->buf);
	if (info->z_buffer)
		ft_free(info->z_buffer);
	if (info->texture)
		ft_free(info->texture);
	if (info->map)
		ft_free_2d(info->map);
	if (info->mlx && info->win)
		mlx_destroy_window(info->mlx, info->win);
	ft_exit(0);
	return (0);
}
