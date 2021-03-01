#include "../mlx/mlx.h"

int		main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "mlx_project"); // 500 * 500 사이즈 윈도우 생성 및 화면표시, 제목 표시줄엔 "mlx_project"
	mlx_loop(mlx);
}
