/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 12:12:19 by hann              #+#    #+#             */
/*   Updated: 2021/02/09 13:20:08 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_info *info)
{
	int	x;

	x = 0;
	// 아래 위 반으로 나눠서 천장과 바닥 색값을 info->buf[]에 저장
	cast_floor_ceiling(info);
	while (x < info->width)
	{
		// camera_x, dir_x, dir_y, map_x, map_y, delta_dist_x, delta_dist_y, hit 저장
		init_ray(info, &info->player, &info->ray, x);
		// step_x, side_dist_x, step_y, side_dist_y 저장
		calculate_step_direction(&info->player, &info->ray);
		// 벽에 부딪혀 hit == 1이 되면 루프 종료
		// (map_x, map_y)에 부딪힌 칸 저장, side 에 부딪힌 방향 저장
		perform_dda(info, &info->ray);
		// prep_wall_dist에 수직거리 저장
		calculate_wall_distance(&info->player, &info->ray);
		// line_height, draw_start, draw_end 저장
		calculate_wall_height(info, &info->ray);
		// wall_x, tex_x 저장
		get_wall_texture(&info->player, &info->ray);
		// 버퍼에 색값 저장
		get_wall_color(info, &info->ray, x);
		// z_buffer에 수직거리 저장
		info->z_buffer[x] = info->ray.perp_wall_dist;
		x++;
	}
}

void	sprite_raycasting(t_info *info, t_player *player)
{
	int	i;
	int	stripe;

	// 거리 큰 것이 앞으로 오도록 정렬
	sort_sprite(info, player);
	i = 0;
	while (i < info->num_sprite)
	{
		// s_ray->screen_x 계산(스프라이트 그릴 중간지점)
		translate_sprite(info, player, &info->s_ray, i);
		// s_ray->height, draw_start_y, draw_end_y 계산
		calculate_sprite_height(info, &info->s_ray);
		// s_ray->draw_start_x, s_ray->draw_end_x 계산
		calculate_sprite_width(info, &info->s_ray);
		// sprite : draw_start_x ~ draw_end_x(화면에서 스프라이트의 모든 수직 줄무늬를 반복)
		stripe = info->s_ray.draw_start_x;
		while (stripe < info->s_ray.draw_end_x)
		{
			// 버퍼에 색값 담기
			get_sprite_color(info, &info->s_ray, stripe);
			stripe++;
		}
		i++;
	}
}

int		main_loop(t_info *info)
{
	raycasting(info);
	sprite_raycasting(info, &info->player);
	draw(info);
	return (0);
}
