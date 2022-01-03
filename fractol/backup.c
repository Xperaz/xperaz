#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>
#include <math.h>

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300
# define MLX_ERROR 1
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17
# define esc  53
# define RIGHT_CLICK 1
# define LEFT_CLICK 2

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int	handle_keypress(int keysym, t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    if (keysym == esc)
        exit(0);
	return (0);
}

int mouse_move(int key, t_data *data)
{
    //mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    if (key == ON_MOUSEUP)
        printf("mouse up\n");
    if (key == ON_MOUSEDOWN)
        printf("mouse down\n");
    if (key == ON_MOUSEMOVE)
        printf("mouse move\n");
    if (key == RIGHT_CLICK)
        printf("rigt click\n");
    if (key == LEFT_CLICK)
        printf("left click\n");
    return (0);
}
int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

    /* circle draww */
    float r = 100;
    float n = 2 * r * 3.14;
    float x, y;

    int color = 0xFF00;
    int i = 0;
    while (i < n)
    {
        int j = 0;
        while (j < n)
        {
            x = i - r;
            y = j - r;
            if (x*x + y*y <= r*r+ 3.14)
                mlx_pixel_put(data.mlx_ptr, data.win_ptr, j, i, color);
            j++;
        }
        color++;
        i++;
    }
	/* Setup hooks */ 
    mlx_key_hook(data.win_ptr, handle_keypress, &data);
    mlx_mouse_hook(data.win_ptr, mouse_move, &data);

    mlx_loop(data.mlx_ptr);
   // mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
