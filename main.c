#include <libft.h>
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

#include <structs.h>
#include <mlx_utils.h>
#include <keycodes.h>

int	mouse_hook(int keycode, t_app *app)
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
	win = mlx_new_window(mlx, 1400, 900, "fract-ol");
	img.img_ptr = mlx_new_image(mlx, 1000, 900);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);

	for (int y = 0; y < 900; ++y)
	{
		for (int x = 0; x < 1000; ++x)
		{
			unsigned char g = x * 255 / 1000;
			unsigned char b = y * 255 / 900;
			img_put_pixel(&img, x, y, rgb_to_int(0, g, b));
		}
	}

	t_app app;
	app.mlx = mlx;
	app.win = win;
	app.img = &img;
	mlx_key_hook(win, mouse_hook, &app);

	// sleep(1);
	mlx_put_image_to_window(mlx, win, img.img_ptr, 0, 0);

	mlx_set_font(mlx, win, "-bitstream-courier 10 pitch-bold-r-normal--0-0-200-200-m-0-iso8859-1");
	mlx_string_put(mlx, win, 1020, 100, 0xEEEEEE, "Hello world");
	mlx_loop(mlx);

	return (0);
}
