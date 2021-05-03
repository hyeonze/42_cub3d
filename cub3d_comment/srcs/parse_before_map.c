/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_before_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <    @student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:47:23 by                   #+#    #+#             */
/*   Updated: 2021/02/15 23:30:14 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_screen_size(t_info *info, char *line)
{
	char	**size;

	// size에 ' '기준 스플릿하여 저장, 실패할 경우 에러처리
	if (!(size = ft_split(line, ' ')))
		return (exit_error(info));
	// size 2개를 얻는데 실패한 경우나, size가 3개 이상일 경우 에러처리
	if (!size || !size[0] || !size[1] || size[2])
		return (exit_error(info));
	// 숫자가 아닌게 섞인 경우 에러처리
	if (!(ft_only_digit(size[0])) || !(ft_only_digit(size[1])))
		return (exit_error(info));
	// R값 두개를 숫자로 width와 height에 저장
	info->width = ft_atoi(size[0]);
	info->height = ft_atoi(size[1]);
	// size 해제
	ft_free_2d(size);
	// atoi를 실패한 경우(숫자가 아닌게 들어온 경우)에러처리
	if (!info->width || !info->height)
		return (exit_error(info));
	return (1);
}

int	get_texture(t_info *info, char *line, char *direction)
{
		// 각 방향 및 스프라이트에 맞게 텍스쳐 경로 저장
	if (direction[0] == 'N' && direction[1] == 'O'\
		&& info->north_texture_path == NULL)
		info->north_texture_path = ft_strdup(line);
	else if (direction[0] == 'S' && direction[1] == 'O'\
		&& info->south_texture_path == NULL)
		info->south_texture_path = ft_strdup(line);
	else if (direction[0] == 'W' && direction[1] == 'E'\
		&& info->west_texture_path == NULL)
		info->west_texture_path = ft_strdup(line);
	else if (direction[0] == 'E' && direction[1] == 'A'\
		&& info->east_texture_path == NULL)
		info->east_texture_path = ft_strdup(line);
	else if (direction[0] == 'S' && direction[1] == '\0'\
		&& info->sprite_texture_path == NULL)
		info->sprite_texture_path = ft_strdup(line);
	// 방향이나 스프라이트가 아닌 경우 에러처리
	else
		return (exit_error(info));
	return (1);
}

int	get_color(t_info *info, char *line, int direction)
{
	char	**rgb;
	int		color;
	int		i;

	if (has_two_comma(line) != 1 || has_many_digit(line) != 1)
		return (exit_error(info));
	// rgb에 ','기준  스플릿하여 숫자 저장, 실패할 경우 에러처리
	if (!(rgb = ft_split(line, ',')))
		return (exit_error(info));
	// rgb에 문자열 3개가 들어오지 않았을 경우, 숫자가 아닌게 섞였을 경우 에러처리
	if ((!rgb || !rgb[0] || !rgb[1] || !rgb[2]) || (!(ft_only_digit(rgb[0]))\
		|| !(ft_only_digit(rgb[1])) || !(ft_only_digit(rgb[2]))))
		return (exit_error(info));
	// color값 0으로 초기화
	// i(인덱스) 초기화
	color = 0;
	i = 0;
	// color에 rgb[0~2]를 16진수 형태로 저장
	while (rgb[i])
	{
		color *= 256;
		ft_atoi(rgb[i]) > 255 ? exit_error(info) : 0;
		color += ft_atoi(rgb[i++]);
	}
	// 0,0,0이 들어온 경우 color == 0이 되어 check_init에 걸리기 때문에 1로 대체
	color = color == 0 ? 1 : color;
	// rgb해제 후 null로
	ft_free_2d(rgb);
	rgb = 0;
	// 첫 문자가 'F'인 경우 info->floor_color에 color 저장
	// 첫 문자가 'C'인 경우 info->ceiling_color에 color 저장
	info->floor_color = direction == 'F' ? color : info->floor_color;
	info->ceiling_color = direction == 'C' ? color : info->ceiling_color;
	return (1);
}

int	parse_line(t_info *i, char *l)
{
	// line이 "R "로 시작할 경우
	// info->width, info->height에 스크린사이즈 저장
	if (ft_strncmp(l, "R ", 2) == 0 && ft_strncmp(l, "R  ", 3) != 0\
		&& i->width == 0 && i->height == 0)
		return (get_screen_size(i, l + 2));
	// line이 "NO ", "SO ", "WE ", "EA ", "R  "로 시작할 경우
	// info->(텍스쳐경로)에 경로 저장
	else if (ft_strncmp(l, "NO ", 3) == 0 && ft_strncmp(l, "NO  ", 4) != 0)
		return (get_texture(i, l + 3, "NO"));
	else if (ft_strncmp(l, "SO ", 3) == 0 && ft_strncmp(l, "SO  ", 4) != 0)
		return (get_texture(i, l + 3, "SO"));
	else if (ft_strncmp(l, "WE ", 3) == 0 && ft_strncmp(l, "WE  ", 4) != 0)
		return (get_texture(i, l + 3, "WE"));
	else if (ft_strncmp(l, "EA ", 3) == 0 && ft_strncmp(l, "EA  ", 4) != 0)
		return (get_texture(i, l + 3, "EA"));
	else if (ft_strncmp(l, "S ", 2) == 0 && ft_strncmp(l, "S  ", 3) != 0)
		return (get_texture(i, l + 2, "S"));
	// line이 "F " 또는 "C "로 시작할 경우
	// info->(floor/ceiling_color)에 색값을 16진수로 바꾸어 저장
	else if (ft_strncmp(l, "F ", 2) == 0 && ft_strncmp(l, "F  ", 3) != 0\
		&& i->floor_color == 0)
		return (get_color(i, l + 2, 'F'));
	else if (ft_strncmp(l, "C ", 2) == 0 && ft_strncmp(l, "C  ", 3) != 0\
		&& i->ceiling_color == 0)
		return (get_color(i, l + 2, 'C'));
	// 빈 라인이 들어온 경우
	// 다음 줄 읽기
	else if (l[0] == '\0')
		return (1);
	return (0);
}

int	parse_cub(t_info *info, char *path)
{
	char	*line;
	int		ret;

	// 인포 초기화
	init_info(info);
	// 입력한 인자 오픈
	info->fd = open(path, O_RDONLY);
	// gnl로 읽기
	while (get_next_line(info->fd, &line) > 0)
	{
		// 요소 형식이 아닌 경우 에러메시지
		// 각 요소를 파싱하여 info->XXX 에 저장(창크기, 텍스쳐경로, 하늘땅색상)
		if ((ret = parse_line(info, line)) == -1)
			return (exit_error(info));
		// 요소나 '/0'이 아닌게 들어오면 맵이 시작됐다고 판단해 break
		if (ret == 0)
			break ;
		// line해제
		free(line);
	}
	// info->map 채우기, 플레이어 위치, 방향, 스프라이트 갯수 저장, 맵 유효성 체크
	if (!read_map(info, line))
		return (exit_error(info));
	// info에서 맵과 관련된 정보가 없을 경우 에러처리
	if (!check_init(info))
		return (exit_error(info));
	// 스프라이트 위치 저장(순서대로)
	if (!set_sprite(info))
		return (exit_error(info));
	return (1);
}
