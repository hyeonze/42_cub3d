/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:42:16 by hann              #+#    #+#             */
/*   Updated: 2021/02/09 12:41:17 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_texture(t_player *player, t_ray *ray)
{
	// wall_x : 광선이 칸 안에서 부딪힌 위치(0~1)
	// 자신의 위치 + 축방향 이동거리를 구해서 총 이동거리를 구한 후(유도과정은 슬랙에 있음)
	if (ray->side <= 1)
		ray->wall_x = player->y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = player->x + ray->perp_wall_dist * ray->dir_x;
	// 소숫점만 취해서 적중지점 계산
	ray->wall_x -= floor(ray->wall_x);
	// tex_x : 텍스쳐 속 x좌표(텍스쳐 너비 곱해서 텍스쳐 속 위치 계산)
	ray->tex_x = (int)(ray->wall_x * (double)TEX_WIDTH);
	// 역방향 광선인 경우 -1 보정(소숫점 취했을 때 잘리는 점)
	if (ray->side == 1 || ray->side == 2)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
}

void	get_wall_color(t_info *info, t_ray *ray, int x)
{
	int	color;
	int	y;

	// step : 텍스쳐 속 이동할 거리, tex_pos : 텍스쳐 속 시작 좌표(슬랙+공책그림)
	// draw_start가 0이 아닌 경우(그릴높이<창높이) tex_pos가 0이 되어 텍스쳐 끝자락부터 그리기 시작(그리기시작점+그릴높이/2-화면절반/2=0)
	// draw_start가 0인 경우(그릴높이>창높이) tex_pos가 넘치는 길이의 반에 step곱한 크기가 됨
	ray->step = 1.0 * TEX_HEIGHT / ray->line_height;
	ray->tex_pos = (ray->draw_start - info->height / 2\
					+ ray->line_height / 2) * ray->step;
	y = ray->draw_start;
	// y : draw_start ~ draw_end
	while (y < ray->draw_end)
	{
		// tex_y : 텍스쳐 속 y좌표, step을 더하다가 텍스쳐보다 커지는 경우를 대비해 텍스쳐 높이로 나눈 나머지를 취함(실제 텍스쳐는 1차포인터라 직선형임, 잘라서 생각)
		ray->tex_y = (int)ray->tex_pos & (TEX_HEIGHT - 1);
		// 텍스쳐 시작좌표에 텍스쳐 이동거리 더해주며 반복
		ray->tex_pos += ray->step;
		// color에 현재 위치의 색값 저장
		color =\
			info->texture[ray->side][TEX_HEIGHT * ray->tex_y + ray->tex_x];
		// 버퍼에 색값 저장
		info->buf[y][x] = color;
		y++;
	}
}
