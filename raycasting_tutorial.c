#include "cub3d.h"

int main()
{
    void    *cub3d;
    void    *win;

    cub3d = mlx_init();
    win = mlx_new_window(cub3d, 1024, 1024, "raycaster");
    mlx_loop(cub3d);
}