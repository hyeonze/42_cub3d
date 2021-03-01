/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:10:40 by hann              #+#    #+#             */
/*   Updated: 2021/02/18 17:23:35 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_info(t_info *info, char *path)
{
	init_player(&info->player);
	if (!parse_cub(info, path))
		return (exit_error(info));
	if (info->width > 2560)
		info->width = 2560;
	if (info->height > 1440)
		info->height = 1440;
	init_player_direction(info);
	info->mlx = mlx_init();
	if (!init_buffer(info))
		return (exit_error(info));
	if (!init_texture(info))
		return (exit_error(info));
	load_texture(info);
	info->img.img = mlx_new_image(info->mlx, info->width, info->height);
	info->img.data = (int *)mlx_get_data_addr(\
		info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
	return (1);
}

int		process_option(t_info *info, int option)
{
	if (option == 1)
	{
		raycasting(info);
		sprite_raycasting(info, &info->player);
		if (!save_bmp(info))
			return (exit_error(info));
		ft_exit(0);
	}
	else
	{
		info->win =\
			mlx_new_window(info->mlx, info->width, info->height, "cub3D");
		mlx_hook(info->win, 2, 0, key_press, info);
		mlx_hook(info->win, 17, 0, ft_exit, 0);
		mlx_loop_hook(info->mlx, main_loop, info);
		mlx_loop(info->mlx);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_info	info;
	int		option;
	int		fd;

	option = (argc >= 2 && (ft_strncmp(argv[1], "--save", 6) == 0)) ? 1 : 0;
	if (argc < option + 2 || argc > option + 2)
		return (exit_error(&info));
	if ((fd = open(argv[option + 1], O_RDONLY)) == -1 ||\
		check_name(argv[option + 1]) == 0)
		return (exit_error(&info));
	if (!set_info(&info, argv[option + 1]))
		return (exit_error(&info));
	if (!process_option(&info, option))
		return (exit_error(&info));
	free_cub(&info);
	return (0);
}
