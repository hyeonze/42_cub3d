/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                  >                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:41:21 by                   #+#    #+#             */
/*   Updated: 2021/02/14 00:16:09 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprite(t_info *info, t_player *player)
{
	int	i;

	// info->sprite[i].distance에 거리제곱 저장
	i = 0;
	while (i < info->num_sprite)
	{
		info->sprite[i].distance =\
			((player->x - info->sprite[i].x)\
				* (player->x - info->sprite[i].x)\
					+ (player->y - info->sprite[i].y)\
						* (player->y - info->sprite[i].y));
		i++;
	}
	// 거리제곱이 큰 것이 앞으로오게 정렬
	sort(info);
}

void	translate_sprite(\
				t_info *info, t_player *player, t_sprite_ray *s_ray, int i)
{
	double	v_mode;

	// v_mode : 커지면 스프라이트가 아래로 내려옴
	v_mode = 0.0;
	// (s_ray->x, s_ray->y) : 직교좌표상 플레이어가 본 스프라이트의 상대적 위치
	s_ray->x = info->sprite[i].x - player->x;
	s_ray->y = info->sprite[i].y - player->y;
	// s_ray->diterminant : 카메라 행렬의 디터미넌트
	s_ray->diterminant = 1.0 /\
		(player->plane_x * player->dir_y - player->dir_x * player->plane_y);
	// transform_x : 스프라이트가 화면안으로 들어가서 얼마나 옆으로 갔는지
	// transform_y : 스프라이트가 화면안으로 들어간 깊이
	s_ray->transform_x = s_ray->diterminant *\
		(player->dir_y * s_ray->x - player->dir_x * s_ray->y);
	s_ray->transform_y = s_ray->diterminant *\
		(-player->plane_y * s_ray->x + player->plane_x * s_ray->y);
	// s_ray->screen_x : 스프라이트가 그려질 중간지점(화면중점 + 화면중점 * 벌어진비율)
	// https://stdbc.tistory.com/67 그림참조 // https://stdbc.tistory.com/67 뷰포트 변환
	s_ray->screen_x = (int)((info->width / 2) *\
						(1 + s_ray->transform_x / s_ray->transform_y));
	// v_move_screen : 커지면 스프라이트 중점이 상승함(draw_start, draw_end에 각각 더해줄 변수)
	s_ray->v_move_screen = (int)(v_mode / s_ray->transform_y);
}

void	calculate_sprite_height(t_info *info, t_sprite_ray *s_ray)
{
	int	v_div;

	// v_div : 스프라이트 높이 조절(스프라이트_height를 vDiv로 나눠주면 길어지거나 납작해진다.)
	v_div = 1;
	// s_ray->height : 그릴 스프라이트 높이(화면높이 / 스프라이트깊이)
	s_ray->height = (int)fabs((info->height / s_ray->transform_y) / v_div);
	// s_ray->draw_start_y : 스프라이트 그리기 시작할 높이(화면높이 절반에서 스프라이트 높이 절반만큼 아래로)
	s_ray->draw_start_y =\
		-s_ray->height / 2 + info->height / 2 + s_ray->v_move_screen;
	// 스프라이트 그리기 시작할 높이가 화면을 벗어난 경우(음수) 0으로 대체
	if (s_ray->draw_start_y < 0)
		s_ray->draw_start_y = 0;
	// s_ray->draw_end_y : 스프라이트 그리기를 끝낼 높이(화면높이 절반에서 스프라이트 높이 절반만큼 위로)
	s_ray->draw_end_y =\
		s_ray->height / 2 + info->height / 2 + s_ray->v_move_screen;
	// 스프라이트 그리기를 끝낼 높이가 화면을 벗어난 경우(화면높이보다 커짐) 화면높이 - 1로 대체
	if (s_ray->draw_end_y >= info->height)
		s_ray->draw_end_y = info->height - 1;
}

void	calculate_sprite_width(t_info *info, t_sprite_ray *s_ray)
{
	int	u_div;

	// u_div : 스프라이트 폭 조절(스프라이트_width를 uDiv로 나눠주면 홀쭉해지거나 뚱뚱해진다.)
	u_div = 1;
	// s_ray->width : 스프라이트 폭(화면)(텍스쳐와 같은 비율로 보여주기 위해 기본값이 s_ray->height와 동일)
	s_ray->width = (int)fabs((info->height / s_ray->transform_y) / u_div);
	// s_ray->draw_start_x : 스프라이트 그리기 시작할 좌측지점(스프라이트 중점에서 스프라이트 폭의 절반만큼 왼쪽으로)
	s_ray->draw_start_x = -s_ray->width / 2 + s_ray->screen_x;
	// 스프라이트 그리기 사작할 좌측지점이 화면을 벗ㅇ어난 경우(음수) 0으로 대체
	if (s_ray->draw_start_x < 0)
		s_ray->draw_start_x = 0;
	// s_ray->draw_end_x : 스프라이트 그리기를 끝낼 우측지점(스프라이트 중점에서 스프라이트 폭의 절반만큼 오른쪽으로)
	s_ray->draw_end_x = s_ray->width / 2 + s_ray->screen_x;
	// 스프라이트 그리기를 끝낼 우측지점이 화면을 벗어난 경우(화면폭보다 커짐) 화면폭 - 1로 대체
	if (s_ray->draw_end_x >= info->width)
		s_ray->draw_end_x = info->width - 1;
}

void	get_sprite_color(t_info *info, t_sprite_ray *s_ray, int stripe)
{
	int	color;
	int	y;
	int	draw;

	// tex_x : 스프라이트그림파일(텍스쳐) 속 x좌표(현위치 -(그릴스프라이트중점 - 그릴스프라이트가로절반)) * 텍스쳐/그릴스프라이트크기
	s_ray->tex_x =\
		(int)(((stripe - (-s_ray->width / 2 + s_ray->screen_x)) *\
			TEX_WIDTH / s_ray->width));
	// 그릴 조건 : 깊이가 양수인 경우(뒤에있는 스프라이트 안그림)
	// 스프라이트가 화면너비 안에 있을 경우(0~info->width), 스프라이트가 벽보다 앞에있을 경우
	if (s_ray->transform_y > 0 && stripe > 0 &&\
		stripe < info->width && s_ray->transform_y < info->z_buffer[stripe])
	{
		// y : s_ray->draw_start_y ~ s_ray->draw_end_y(스프라이트 아래끝 ~ 위끝)
		y = s_ray->draw_start_y;
		while (y < s_ray->draw_end_y)
		{
			// draw : y의 이동에 따라 0 ~ s_ray->height(그릴 스프라이트 높이) 이동(y - 화면높이절반 + 그릴스프라이트높이절반)
			draw = (y - s_ray->v_move_screen) -\
					info->height * 0.5 + s_ray->height * 0.5;
			// s_ray->tex_y : 스프라이트그림파일(텍스쳐)속 y좌표(텍스쳐 높이로 나누고 텍스쳐 높이 곱했다)
			s_ray->tex_y = ((draw * TEX_HEIGHT) / s_ray->height);
			// 텍스쳐 위치의 색값을 color에 저장
			color = info->texture[4][TEX_WIDTH * s_ray->tex_y + s_ray->tex_x];
			// color값이 검은색이 아니면 버퍼에 담는다
			if ((color & 0x00FFFFFF) != 0)
				info->buf[y][stripe] = color;
			y++;
		}
	}
}
