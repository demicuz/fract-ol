#include <stdio.h>
#include <unistd.h>
#include <libft.h>
#include <mlx.h>

#include <mlx_utils.h>
#include <keycodes.h>
#include <params.h>

int	mouse_hook(int keycode, t_app *app)
{
	printf("Hello from key %d\n", keycode);
	// mlx_put_image_to_window(app->mlx, app->win, app->img->img_ptr, 0, 0);
	return (0);
}

int	key_hook(int keycode, t_app *app)
{
	if (keycode == ESC)
		exit(0);
	printf("Hello from key %d\n", keycode);
	mlx_put_image_to_window(app->mlx, app->win, app->img->img_ptr, 0, 0);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*win;
	t_imgdata	img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, W, H, "fract-ol");
	img.img_ptr = mlx_new_image(mlx, VIEW_W, VIEW_H);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.width = VIEW_W;
	img.height = VIEW_H;

	img_fill(&img, 0x00AAFF);

	t_app app;
	app.mlx = mlx;
	app.win = win;
	app.img = &img;
	mlx_mouse_hook(win, mouse_hook, &app);
	mlx_key_hook(win, key_hook, &app);
	// mlx_loop_hook();
	// mlx_hook();

	// sleep(1);
	mlx_put_image_to_window(mlx, win, img.img_ptr, 0, 0);

	mlx_set_font(mlx, win, "-bitstream-courier 10 pitch-bold-r-normal--0-0-200-200-m-0-iso8859-1");
	mlx_string_put(mlx, win, 1020, 100, 0xEEEEEE, "Hello world");
	mlx_loop(mlx);

	return (0);
}
