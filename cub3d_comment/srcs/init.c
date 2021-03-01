/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:42:44 by hann              #+#    #+#             */
/*   Updated: 2021/02/08 12:37:38 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_info(t_info *info)
{
	info->width = 0;
	info->height = 0;
	info->map_width = 0;
	info->map_height = 0;
	info->map = NULL;
	info->buf = NULL;
	info->z_buffer = NULL;
	info->north_texture_path = NULL;
	info->south_texture_path = NULL;
	info->west_texture_path = NULL;
	info->east_texture_path = NULL;
	info->sprite_texture_path = NULL;
	info->floor_color = 0;
	info->ceiling_color = 0;
	info->num_sprite = 0;
	info->sprite = NULL;
}

void	init_player(t_player *player)
{
	player->x = 2;
	player->y = 5;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
	player->move_speed = 0.05;
	player->rot_speed = 0.05;
}

int		init_buffer(t_info *info)
{
	int	i;

	i = 0;
	// info->buf에 맵 높이갯수의 2차포인터 할당하고, 0으로 채움
	if (!(info->buf = ft_calloc(info->height, sizeof(int **))))
		return (exit_error(info));
	// 각 info->buf[i]에 맵 폭갯수의 1차포인터 할당하고, 0으로 채움
	while (i < info->height)
	{
		if (!(info->buf[i] = ft_calloc(info->width, sizeof(int *))))
			return (exit_error(info));
		i++;
	}
	// info->z_buffer에 맵 폭갯수의 1차포인터 할당하고, 0으로 채움
	if (!(info->z_buffer = ft_calloc(info->width, sizeof(double *))))
		return (exit_error(info));
	return (1);
}

int		init_texture(t_info *info)
{
	int	i;
	int	j;

	// info->texture에 이차포인터(일차포인터 5개) 할당
	if (!(info->texture = (int **)malloc(sizeof(int *) * 5)))
		return (-1);
	i = 0;
	// info->texture[0~4]에 텍스쳐 가*세 만큼의 메모리 할당 후 0채우기
	while (i < 5)
	{
		if (!(info->texture[i] =\
				(int *)malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH))))
			return (-1);
		j = 0;
		while (j < TEX_HEIGHT * TEX_WIDTH)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	return (1);
}

int		init_map(t_info *info, t_list *lst)
{
	int	i;
	int	j;

	// info->map_height에 노드갯수 저장(맵 세로크기가 됨)
	info->map_height = ft_lstsize(lst);
	// info->map(2차원배열)에 map_height개의 1차포인터 할당, 실패 시 에러처리
	if (!(info->map = (char **)malloc(sizeof(char *) * (info->map_height))))
		return (exit_error(info));
	// 인덱스 i 초기화
	i = 0;
	// map_width에 1차포인터 중 가장 긴 길이 저장(맵 가로크기가 됨)
	info->map_width = get_max_line_size(lst);
	while (lst)
	{
		// 각각의 info->map[i]에 map_width+1 크기의 메모리 할당, 실패시 에러
		if (!(info->map[i] =\
				(char *)malloc(sizeof(char) * (info->map_width + 1))))
			return (exit_error(info));
		// 인덱스 j 초기화
		j = 0;
		// 각 라인 길이만큼 info->map[i][j]값 0으로 초기화
		while (j++ < (int)ft_strlen(lst->content))
			info->map[i][j] = 0;
		// 라인이 끝나면 공백으로 채움
		while (j++ < info->map_width)
			info->map[i][j] = ' ';
		// 마지막 칸 null값 채움
		info->map[i][info->map_width] = '\0';
		// 인덱스 추가
		i++;
		// 다음노드로 이동
		lst = lst->next;
	}
	return (1);
}
