/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:22:24 by hann              #+#    #+#             */
/*   Updated: 2021/02/16 17:49:45 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map(t_info *info, t_list *lst)
{
	// info->map 초기화(일단 0과 ' '으로 채움)
	if (!init_map(info, lst))
		return (exit_error(info));
	// info->map 채우기, 플레이어 위치, 방향, 스프라이트 갯수 저장
	if (!fill_map(info, lst))
		return (exit_error(info));
	// 연결리스트 비우기
	ft_lstclear(&lst, free);
	// 맵 유효성 체크
	if (!check_valid_map(info))
		return (exit_error(info));
	return (1);
}

int	read_map(t_info *info, char *line)
{
	t_list	*lst;

	// info->map_width, info->map_height 초기화
	info->map_width = 0;
	info->map_height = 0;
	// 연결리스트를 생성하고, line의 내용 저장
	lst = ft_lstnew(ft_strdup(line));
	// line 해제
	free(line);
	// gnl로 다음 라인을 계속 읽어 다음 노드에 저장
	while (get_next_line(info->fd, &line) > 0)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	// 마지막 노드 저장
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(line)));
	free(line);
	// 맵 파싱, info->map 채우기, 플레이어 위치, 방향, 스프라이트 갯수 저장, 맵 유효성 체크
	if (!parse_map(info, lst))
		return (exit_error(info));
	return (1);
}

int	init_direction(t_info *info, int i, int j, int *dir_count)
{
	// "NSEW"중 하나가 들어온 경우
	if (is_dir(info->map[i][j]) == 1)
	{
		// info->dir에 방향저장, info->player.x, info->player.y에 플레이어 위치 저장
		info->dir = info->map[i][j];
		info->player.x = 0.5f + j;
		info->player.y = 0.5f + i;
		// dir_count 1 증가
		(*dir_count)++;
	}
	// '2'가 들어온 경우 info->num_sprite 1 증가
	if (info->map[i][j] == '2')
		info->num_sprite++;
	return (1);
}

int	fill_map(t_info *info, t_list *lst)
{
	int		i;
	int		j;
	char	*line;
	int		dir_count;

	i = -1;
	dir_count = 0;
	while (++i < info->map_height)
	{
		j = -1;
		// line에 lst->content 저장
		line = (char *)lst->content;
		// line이 끝날 때 까지
		while (++j < (int)ft_strlen(line))
		{
			// 맵에 사용되는 문자가 아닌 경우 에러처리
			if (is_map_arg(line[j]) == -1)
				return (exit_error(info));
			// info->map[i][j]에 line[j]내용 저장
			info->map[i][j] = line[j];
			// 방향이 들어온 경우 방향, 플레이어 위치 저장, dir_count 1 증가
			// 2가 들어온 경우 info->num_sprite 1증가
			init_direction(info, i, j, &dir_count);
		}
		// 다음 노드로
		lst = lst->next;
	}
	// dir_count가 1이 아닌 경우 에러처리
	if (dir_count == 0 || dir_count > 1)
		return (exit_error(info));
	return (1);
}

int	check_valid_map(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// 첫 줄에 ' '또는 '1'이 아닌 것이 들어오면 에러처리
	if (!check_map_top(info))
		return (exit_error(info));
	// 모든 라인 체크
	while (i < info->map_height - 1)
	{
		j = 0;
		// 맵 시작이 1인지 체크
		if (!check_map_left(info, i, j))
			return (exit_error(info));
		
		while (j < (int)ft_strlen(info->map[i]))
		{
			// 맵 중간 테스트(1로 시작하는지, 공백 도중 딴게 나오는지, '  ', ' 1', '1 ')
			if (!check_map_middle(info, i, j))
				return (exit_error(info));
			j++;
		}
		// 맵 우측 끝 1 체크
		if (!check_map_right(info, i, j))
			return (exit_error(info));
		i++;
	}
	// 끝 줄에 ' '또는 '1'이 아닌 것이 들어오면 에러처리
	if (!check_map_bottom(info, i))
		return (exit_error(info));
	return (1);
}
