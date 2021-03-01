#include <stdio.h>
#include "../mlx/mlx.h"
typedef struct s_img
{
	void		*ptr;
	int			*data;
	int			width;
	int			height;


	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

int main()
{
		void	*mlx;
		void	*win;
		t_img	img;
		int		count_h;
		int		count_w;


		mlx = mlx_init();
		win = mlx_new_window(mlx, 500, 500, "my_mlx");
		// 500 * 500 사이즈 윈도우 생성 및 화면표시, 이름은 "mymlx"
		img.ptr = mlx_xpm_file_to_image(mlx, "../textures/wall_s.xpm", &img.width, &img.height);
		// mpm파일을 이미지로 변환 후 해당 이미지 포인터를 img.ptr에 저장, img.width와 img.height에는 이미지크기 저장
		img.data = (int *)mlx_get_data_addr(img.ptr, &img.bpp, &img.size_l, &img.endian);
		// img_ptr와 int형 변수의 주소들을 넘겨주면 char형 배열의 주소 반환
		// bits_per_pixel(img.bpp): 한 픽셀을 표현하는 데 필요한 비트 수
		// size_line(img.size_l): 이미지의 width를 표현하는 데 필요한 바이트 수
		// endian: 리틀 엔디언일 시 0, 빅 엔디언일 시 1
		count_h = -1;
		while (++count_h < img.height)
		{
			count_w = -1;
			while (++count_w < img.width / 2)
			{
				if (count_w % 2)
					img.data[count_h * img.width + count_w] = 0xFFFFFF;
				else
					img.data[count_h * img.width + count_w] = 0xFF0000;
			}
		}
		// 배열에 접근해서 이미지 정보 수정
		mlx_put_image_to_window(mlx, win, img.ptr, 50, 50);
		mlx_loop(mlx);
		return (0);
}
