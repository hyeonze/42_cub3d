//Character '북' on the screen means 'North' in Korean.
#include <stdio.h>
#include "../mlx/mlx.h"

int main()
{
		void *mlx;
		void *win;
		void *img;

		int		img_width;
		int 	img_height;

		mlx = mlx_init();
		win = mlx_new_window(mlx, 500, 500, "my_mlx");
		img = mlx_xpm_file_to_image(mlx, "../textures/wall_n.xpm", &img_width, &img_height);
		// filename과 int형 변수의 주소값을 넘겨주면
		// xpm 파일을 이미지로 변환 후 해당 이미지 포인터 반환.
		// int형 변수에는 해당 이미지의 width, height 저장.
		mlx_put_image_to_window(mlx, win, img, 50, 50);
		//win_ptr에 해당되는 창의 (x, y)에 이미지를 그린다.
		//(이미지의 좌상단 기준 좌표)
		mlx_loop(mlx);
		return (0);
}
