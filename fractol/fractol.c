#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <math.h>

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 1080
# define MLX_ERROR 1
# define MAX 30

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
    void    *img;
}	t_data;

int	handle_keypress(int keysym, t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    exit(1);
	return (0);
}

int		color_set(int iter)
{
	double	r;
	double	g;
	double	b;
	int		color;

	r = sin(0.3 * (double)iter);
	g = sin(0.3 * (double)iter + 3) * 127 + 128;
	b = sin(0.3 * (double)iter + 3) * 127 + 128;
	color = ((int)(0 * r) << 16) + ((int)(255 * g) << 8) + ((int)(255 * b));
	return (color);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Mendelbrot/julia set");
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 1200, 1080);
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
    /* drawing */
    for (int row = 0; row < WINDOW_HEIGHT; row++) {
    for (int col = 0; col < WINDOW_WIDTH; col++) {
        double c_re = (col - WINDOW_WIDTH / 2.0) * 4.0/WINDOW_WIDTH;
        double c_im = (row - WINDOW_HEIGHT / 2.0) * 4.0/WINDOW_HEIGHT;
        double x = 0, y = 0;
        int iteration = 0;
        while (x * x + y * y <= 4 && iteration < MAX) {
            double x_new = x * x - y * y + c_re;
            y = 2 * x * y + c_im;
            x = x_new;
            iteration++;
        }
        if (iteration < MAX)
			mlx_pixel_put(data.mlx_ptr, data.win_ptr, col, row, color_set(iteration));
        else 
			mlx_pixel_put(data.mlx_ptr, data.win_ptr, col, row, 0x000000);
    }
}

	/* Setup hooks */ 
    mlx_hook(data.win_ptr, 2, 1L<<0, handle_keypress, &data);
	
    mlx_loop(data.mlx_ptr);
   // mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
