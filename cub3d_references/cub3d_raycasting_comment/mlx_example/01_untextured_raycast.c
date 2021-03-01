/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_untextured_raycast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:12:25 by yohan             #+#    #+#             */
/*   Updated: 2021/01/11 15:19:32 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	double	moveSpeed;
	double	rotSpeed;
}				t_info;

int	worldMap[24][24] = {
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
						};

// 수직선 그려주는 함수
void	verLine(t_info *info, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(info->mlx, info->win, x, y, color);
		y++;
	}
}

void	calc(t_info *info)
{
	int	x;

	x = 0; // 수직선에 대해서 계산
	while (x < width)
	{
		// cameraX : 카메라 평면에서의 x좌표(-1 ~ 1)
		double cameraX = 2 * x / (double)width - 1;
		
		// (rayDirX, rayDirY) : 광선의 방향벡터
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;
		
		// mapX, mapY : 현재 광선의 위치(광선이 있는 칸)
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		// length of ray from current position to next x or y-side
		// sideDistX : 시작점 ~ 첫번째 x면을 만나는 점 까지 광선의 이동거리(첫거리)
		// sideDistY : 시작점 ~ 첫번째 y면을 만나는 점 까지 광선의 이동거리(첫거리)
		double sideDistX;
		double sideDistY;
		
		// length of ray from one x or y-side to next x or y-side
		// deltaDistX : '시작점 ~ 첫번째 x면을 만나는 점'까지의 광선의 이동거리(고정거리)
		// deltaDistY : '시작점 ~ 첫번째 y면을 만나는 점'까지의 광선의 이동거리(고정거리)
		double deltaDistX = fabs(1 / rayDirX); // 역수 취하면 수평선과 다시 만날 때 까지 광선이 이동한 거리가 나옴 // 이 때 분자1은 방향벡터의 크기라 아무숫자가 들어간 것
		double deltaDistY = fabs(1 / rayDirY); // 역수 취하면 수직선과 다시 만날 때 까지 광선이 이동한 거리가 나옴
		double perpWallDist; // perWallDist : 광선의 이동거리를 계산하는데 사용할 것
		
		// what direction to step in x or y-direction (either +1 or -1)
		// stepX, stepY : 어느 방향으로 건너뛰는지 표식(광선의 방향에 따라, -1 또는 1 중 하나만 선택적으로 적용)
		int stepX;
		int stepY;
		
		int hit = 0; // was there a wall hit? // 벽과 부딪혔는지 여부(루브 종료조건)
		int side; //was a NS or a EW wall hit? // 벽과 부딪혔고 x면에 부딪힌거면 0, y 면에 부딪히면 1

		// DDA 알고리즘 시작 전 stepX, stepY, sideDistX, sideDistY 초기화
		// 광선의 x방향 rayDirX의 값이 양수면 stepX는 1, 음수라면 -1 // rayDirX의 값이 0이면 stepX의 값은 아무 값이든 상관없음 // stepY도 같은 방법으로 구해줌
		// sideDistX : rayDirX가 양수이면 '광선의 시작점부터 오른쪽 으로 이동하다 처음 만나는 x면까지의 거리', 음수이면 '광선의 시작점부터 왼쪽 으로 이동하다 처음 만나는 x면까지의 거리' 
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}

		// DDA알고리즘 시작
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0; // 벽의 x면에 부딪힌 경우
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1; // 벽의 y면에 부딪힌 경우
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		
		// Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		// 어안렌즈 효과를 방지하는 코드
		if (side == 0) // 벽의 x면에 부딪힌 경우
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else // 벽의 y면에 부딪힌 경우
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		// Calculate height of line to draw on screen
		// lineHeight : 화면에 그려야 할 수직선 높이
		// 멀리 있는게 작게 그려지기 위해 역수 취한 뒤 높이 곱해줌
		int lineHeight = (int)(height / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		// drawStart : 그리기 시작하는 점 (화면높이절반 - 그릴높이절반), 위에서부터 그림
		// drawEnd   : 그리기가 끝나는 점 (화면높이절반 + 그릴높이절반)
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0) // 최고점이 0보다 작으면 0으로 대체
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height) // 최하점이 화면높이보다 크면 화면크기로 대체
			drawEnd = height - 1;

		// choose wall color
		int	color;
		if (worldMap[mapY][mapX] == 1)
			color = 0xFF0000; // red
		else if (worldMap[mapY][mapX] == 2)
			color = 0x00FF00; // green
		else if (worldMap[mapY][mapX] == 3)
			color = 0x0000FF; // blue
		else if (worldMap[mapY][mapX] == 4)
			color = 0xFFFFFF; // white
		else
			color = 0xFFFF00; // yellow
		
		if (side == 1) // y면에 부딪힌 경우 색을 어둡해해서 입체효과를 줌
			color = color / 2;

		verLine(info, x, drawStart, drawEnd, color); // x축 고정 상태에서 y를 drawStart ~ drawEnd 이동시키며 color색으로 한 픽셀씩 찍는 함수
		
		x++;
	}
}

int	main_loop(t_info *info)
{
	calc(info);
	// mlx_put_image_to_window(info->mlx, info->win, &info->img, 0, 0);

	return (0);
}

int	key_press(int key, t_info *info)
{
	if (key == K_W)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	//rotate to the right
	if (key == K_D)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (key == K_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (key == K_ESC)
		exit(0);
	return (0);
}

int	main(void)
{
	t_info info;
	info.mlx = mlx_init();

	// 플레이어 초기 위치벡터
	info.posX = 12;
	info.posY = 5;

	// 플레이어 초기 방향벡터
	info.dirX = -1;
	info.dirY = 0;

	// 플레이어 카메라평면
	info.planeX = 0;
	info.planeY = 0.66;

	
	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;
	
	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	mlx_loop_hook(info.mlx, &main_loop, &info); // main_loop함수 실행
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);

	mlx_loop(info.mlx);
}
