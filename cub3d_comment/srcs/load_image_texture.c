/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                  >                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:47:13 by                   #+#    #+#             */
/*   Updated: 2021/02/16 12:37:53 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int		x;
	int		y;

	// 이미지포인터 저장
	img->img = mlx_xpm_file_to_image(\
					info->mlx, path, &img->width, &img->height);
	// 이미지 데이터 수정
	img->data = (int *)mlx_get_data_addr(\
					img->img, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	// texture에 복사
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] =\
					img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	// 이미지 제거
	mlx_destroy_image(info->mlx, img->img);
}

int		check_texture_file_exists(t_info *info)
{
	int we;
	int ea;
	int so;
	int no;
	int sp;
	
	if ((we = open(info->west_texture_path, O_RDONLY)) == -1)
		return (0);
	if ((ea = open(info->east_texture_path, O_RDONLY)) == -1)
		return (0);
	if ((so = open(info->south_texture_path, O_RDONLY)) == -1)
		return (0);
	if ((no = open(info->north_texture_path, O_RDONLY)) == -1)
		return (0);
	if ((sp = open(info->sprite_texture_path, O_RDONLY)) == -1)
		return (0);
	close(we);
	close(so);
	close(ea);
	close(no);
	close(sp);
	return (1);
}

void	load_texture(t_info *info)
{
	t_img	img;

	if(check_texture_file_exists(info) == 0)
	{
		ft_free(info->north_texture_path);
		ft_free(info->south_texture_path);
		ft_free(info->west_texture_path);
		ft_free(info->east_texture_path);
		ft_free(info->sprite_texture_path);
		exit_error(info);
	}
	load_image(info, info->texture[3], info->north_texture_path, &img);
	load_image(info, info->texture[2], info->south_texture_path, &img);
	load_image(info, info->texture[0], info->west_texture_path, &img);
	load_image(info, info->texture[1], info->east_texture_path, &img);
	load_image(info, info->texture[4], info->sprite_texture_path, &img);
	ft_free(info->north_texture_path);
	ft_free(info->south_texture_path);
	ft_free(info->west_texture_path);
	ft_free(info->east_texture_path);
	ft_free(info->sprite_texture_path);
}
