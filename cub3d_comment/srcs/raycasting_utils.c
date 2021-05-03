/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                  >                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:32:11 by                   #+#    #+#             */
/*   Updated: 2021/02/08 12:39:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_info *info, t_player *player, t_ray *ray, int x)
{
	// camera_x : 카메라 평면에서의 x좌표(-1 ~ 1)
	ray->camera_x = 2 * x / (double)info->width - 1;
	// (dir_x, dir_y) : 광선의 방향벡터
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	// (map_x, map_y) : 광선의 현재위치(광선이 있는 칸)
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	// (delta_dist_x, delta_dist_y) : 광선의 고정 이동거리(유도는 공책에)
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	// hit : 벽과 부딪혔는지 여부
	ray->hit = 0;
}

void	calculate_step_direction(t_player *player, t_ray *ray)
{
	// step_x : 광선의 방향벡터x값이 음수면 -1, 양수면 1(0이면 상관없음)
	// side_dist_x : 첫 이동거리 저장(https://github.com/365kim/raycasting_tutorial/blob/master/3_untextured_raycaster.md, 그림9)
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	// step_y : 광선의 방향벡터y값이 음수면 -1, 양수면 1(0이면 상관없음)
	// side_dist_y : 첫 이동거리 저장(https://github.com/365kim/raycasting_tutorial/blob/master/3_untextured_raycaster.md, 그림9)
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_info *info, t_ray *ray)
{
	while (ray->hit == 0)
	{
		// y방향으로 많이 간 경우 x방향으로 뛰고 side_dist_x다시 저장
		// x면에 부딪혔고, 스탭방향이 음수면 side : 0
		// x면에 부딪혔고, 스탭방향이 양수면 side : 1
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = (ray->step_x == -1) ? 0 : 1;
		}
		else
		// x방향으로 많이 간 경우 y방향으로 뛰고 side_dist_y다시 저장
		// y면에 부딪혔고, 스탭방향이 음수면 side : 2
		// y면에 부딪혔고, 스탭방향이 양수면 side : 3
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = (ray->step_y == -1) ? 2 : 3;
		}
		// 벽에 부딪힌 경우루프 종료
		if (info->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_distance(t_player *player, t_ray *ray)
{
	// 벽의 x면(세로선)에 부딪힌 경우
	// prep_wall_dist : 닮음으로 계산한 수직거리
	// (1 - ray->step_x) / 2) : 스탭 방향에 따른 거리를 보정
	if (ray->side <= 1)
		ray->perp_wall_dist =\
			(ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->dir_x;
	// 벽의 y면(가로선)에 부딪힌 경우
	// prep_wall_dist : 닮음으로 계산한 수직거리
	// (1 - ray->step_y) / 2) : 스탭 방향에 따른 거리를 보정
	else
		ray->perp_wall_dist =\
			(ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->dir_y;
}

void	calculate_wall_height(t_info *info, t_ray *ray)
{
	// line_height : 화면에 그려야 할 수직선 높이(멀리있는게 작게그려지게 하기위해 역수취한 후 화면높이 곱)
	ray->line_height = (int)(info->height / ray->perp_wall_dist);
	// draw_start : 그리기 시작하는 점 (화면높이절반 - 그릴높이절반), 위에서부터 그림
	ray->draw_start = -ray->line_height / 2 + info->height / 2;
	// 최고점이 0보다 작을 경우 0으로 대체
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	// draw_end : 그리기가 끝나는 점(화면높이절반 + 그릴높이절반)
	ray->draw_end = ray->line_height / 2 + info->height / 2;
	// 최하점이 화면높이보다 클 경우 화면높이 - 1로 대체
	if (ray->draw_end >= info->height)
		ray->draw_end = info->height - 1;
}
