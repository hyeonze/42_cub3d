/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                  >                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 10:10:40 by                   #+#    #+#             */
/*   Updated: 2021/02/18 17:24:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_info(t_info *info, char *path)
{
	// 플레이어 기본값 초기화
	init_player(&info->player);
	// cub파일 파싱해서 필요한 정보 저장
	if (!parse_cub(info, path))
		return (exit_error(info));
	// 너무 큰 창크기가 들어온 경우 줄이기
	if (info->width > 2560)
	    info->width = 2560;
    if (info->height > 1440)
        info->height = 1440;
	// 플레이어 방향에 맞게 회전
	init_player_direction(info);
	info->mlx = mlx_init();
	// info->buf에 맵크기 이차포인터 할당하고 0채우기, info->z_buffer에 맵폭크기 일차포인터 할당하고 0채우기
	if (!init_buffer(info))
		return (exit_error(info));
	// info->texture[0~4]에 텍스쳐 크기 할당하고 0채우기
	if (!init_texture(info))
		return (exit_error(info));
	// info->texture 텍스쳐로 채우기
	load_texture(info);
	// info->img.img에 info->width * info->height 크기의 빈 이미지 생성
	info->img.img = mlx_new_image(info->mlx, info->width, info->height);
	// info->img.data에 이미지 정보를 저장해 차후에 이미지 수정할 수 있도록
	info->img.data = (int *)mlx_get_data_addr(\
		info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
	return (1);
}

int		process_option(t_info *info, int option)
{
	// --save옵션이 들어온 경우
	if (option == 1)
	{
		// 레이캐스팅하여 버퍼에 색값 저장, z_buffer에 수직거리 저장
		raycasting(info);
		// 스프라이트위치의 버퍼에 색값 저장
		sprite_raycasting(info, &info->player);
		// "screenshot.bmp"열고 bmp헤더 작성 후 "screenshot.bmp"에 버퍼의 색값 저장
		if (!save_bmp(info))
			return (exit_error(info));
		ft_exit(0);
	}
	// cub만 들어온 경우
	else
	{
		// width * height 크기 윈도우 생성 및 표시, 제목 표시줄에 "cub3D"
		info->win =\
			mlx_new_window(info->mlx, info->width, info->height, "cub3D");
		// 키 눌림감지 시 key_press 함수 실행
		mlx_hook(info->win, 2, 0, key_press, info);
		// esc or 종료버튼 눌림 시 ft_exit 함수 실행
		mlx_hook(info->win, 17, 0, ft_exit, 0);
		// 아무 이벤트도 발생하지 않았을 경우 main_loop 함수 실행(raycasting>spritecasting>draw)
		mlx_loop_hook(info->mlx, main_loop, info);
		// 이벤트 입력 대기하는 함수(exit할 때 까지)
		mlx_loop(info->mlx);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_info	info;
	int		option;
	int		fd;

	// 인자가 두개고 둘째인자가 "--save"인 경우(option : 1)와, 나머지 경우(option : 0) 따로 처리
	option = (argc >= 2 && (ft_strncmp(argv[1], "--save", 6) == 0)) ? 1 : 0;
	// 인자가 갯수가 적거나 많을 경우 에러처리
	if (argc < option + 2 || argc > option + 2)
		return (exit_error(&info));
	// 파일 열기 실패할 경우, 파일이름 .cub로 안끝날 경우 에러처리
	if ((fd = open(argv[option + 1], O_RDONLY)) == -1 ||\
		check_name(argv[option + 1]) == 0)
		return (exit_error(&info));
	// 기본값저장(플레이어 기본값, cub파일 정보, 플레이어 회전, info->buf 및 info->z_buffer 초기화, info->texture 채우기, 빈이미지 생성 후 배열화)
	if (!set_info(&info, argv[option + 1]))
		return (exit_error(&info));
	// option==1이면 bmp처리, option==0이면 창 띄워서 레이캐스팅 draw
	if (!process_option(&info, option))
		return (exit_error(&info));
	// info 해제
	free_cub(&info);
	return (0);
}
