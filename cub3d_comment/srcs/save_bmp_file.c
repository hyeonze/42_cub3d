/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:51:12 by hann              #+#    #+#             */
/*   Updated: 2021/02/08 12:39:29 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void	write_bmp_header(t_info *info, int fd, int size)
{
	// https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
	// https://dojang.io/mod/page/view.php?id=703
	unsigned char	header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	set_int_in_char(header + 2, size);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	set_int_in_char(header + 18, info->width);
	set_int_in_char(header + 22, info->height);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
}

void	write_data(t_info *info, int fd)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					pad;

	i = info->height;
	pad = (4 - (info->width * 3) % 4) % 4;
	// 4바이트씩 처리한 후 남은 칸 zero로
	while (i >= 0)
	{
		j = 0;
		while (j < info->width)
		{
			write(fd, &(info->buf[i][j]), 3);
			if (pad > 0)
				write(fd, &zero, pad);
			j++;
		}
		i--;
	}
}

int		save_bmp(t_info *info)
{
	int	fd;
	int	size;

	size = 54 + 3 * info->width * info->height;
	// 쓰기전용, 파일이 없을경우 생성, 이미 있는경우 내용을 모두 지우고 파일길이를0으로, 파일 기록 시 파일의 맨 끝에 내용추가, 00700 모드로 파일 소유자에게 읽기, 쓰기, 쓰기 실행권한을 준다.
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT |\
						O_TRUNC | O_APPEND, S_IRWXU)) < 0)
		return (0);
	// bmp헤더 작성
	write_bmp_header(info, fd, size);
	// 버퍼에서 파일로 색값 저장
	write_data(info, fd);
	return (1);
}
