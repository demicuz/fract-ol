#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <libft.h>
#include <mlx.h>

#include <mlx_utils.h>
#include <keycodes.h>
#include <params.h>

void	draw_fractal(t_app *app, t_imgdata *imgdata, t_frdata *frdata);

// TODO use long double or double?
// long double arithmetic is significantly slower
t_color	get_mandelbrot_pixel(t_frdata *f, unsigned int *iter_accum, double c_re, double c_im)
{
	int iter = 0;
	double re = c_re;
	double im = c_im;
	double re_prev = c_re;

	while (iter < f->max_iter)
	{
		if (re * re + im * im > 4.0)
			return (t_color) (0xFF * (f->max_iter - iter) / f->max_iter);
		re_prev = re;
		re = re * re - im * im + c_re;
		im = 2.0 * re_prev * im + c_im;
		iter++;
		(*iter_accum)++;
	}
	return 0x000000;
}

void	update_window(t_app *app, int update_fractal)
{
	puts("called update_window");
	mlx_do_sync(app->mlx);

	// mlx_clear_window(app->mlx, app->win);
	if (update_fractal)
		draw_fractal(app, app->img, app->fractal);
	mlx_put_image_to_window(app->mlx, app->win, app->img->img_ptr, 0, 0);
	mlx_string_put(app->mlx, app->win, 50, 50, 0xEEEEEE, "fract-ol");
	// mlx_string_put(app->mlx, app->win, 50, 80, 0xEEEEEE, "max_iter:");
	// char *zoom_str = ft_itoa(app->fractal->max_iter);
	// if (zoom_str)
	// {
	// 	mlx_string_put(app->mlx, app->win, 200, 80, 0xEEEEEE, zoom_str);
	// 	free(zoom_str);
	// }
}

//  0  1 2 3 4
// -2 -1 0 1 2

//  0  1 2 3 4 5
// -2 -1 0 1 2

void	draw_fractal(t_app *app, t_imgdata *imgdata, t_frdata *frdata)
{
	int half_w = imgdata->width / 2;
	int half_h = imgdata->height / 2;
	unsigned int iter_accum = 0;

	for (int y = 0; y < imgdata->height; ++y)
	{
		for (int x = 0; x < imgdata->width; ++x)
		{
			double lx = (double) (x - half_w) * frdata->zoom / imgdata->width - frdata->x;
			double ly = (double) (y - half_h) * frdata->zoom * ASPECT_RATIO / imgdata->height - frdata->y;
			t_color color = 0xFFFFFF;
			color = get_mandelbrot_pixel(frdata, &iter_accum, lx, ly);
			img_put_pixel(imgdata, x, imgdata->height - y - 1, color);
			if (iter_accum > ITERS_PER_PASS)
			{
				update_window(app, 0);
				iter_accum = 0;
			}
		}
	}
}

int	mouse_hook(int keycode, int x, int y, t_app *app)
{
	printf("Mouse keycode %d, x: %d, y: %d\n", keycode, x, y);

	double x_rel = ((double) - app->img->width / 2 + x) / app->img->width;
	double y_rel = ((double) app->img->height / 2 - y) * ASPECT_RATIO / app->img->height;
	printf("relative, x: %lf, y: %lf\n", x_rel, y_rel);

	if (keycode == WHEEL_UP)
	{
		app->fractal->zoom *= 0.5;
		app->fractal->x -= x_rel * app->fractal->zoom;
		app->fractal->y -= y_rel * app->fractal->zoom;
		update_window(app, 1);
	}
	else if (keycode == WHEEL_DOWN)
	{
		app->fractal->x += x_rel * app->fractal->zoom;
		app->fractal->y += y_rel * app->fractal->zoom;
		app->fractal->zoom *= 2.0;
		update_window(app, 1);
	}
	return (0);
}

int	key_hook(int keycode, t_app *app)
{
	printf("Keyboard keycode: %d\n", keycode);
	if (keycode == ESC)
		exit(0);
	if (keycode == R)
	{
		app->fractal->zoom = 4.0;
		app->fractal->x = 0.5;
		app->fractal->y = 0.0;
		app->fractal->max_iter = 100;
	}
	// TODO add bounds
	else if (keycode == COMMA)
	{
		app->fractal->max_iter -= 100;
		printf("max_iter: %d\n", app->fractal->max_iter);
	}
	else if (keycode == DOT)
	{
		app->fractal->max_iter += 100;
		printf("max_iter: %d\n", app->fractal->max_iter);
	}
	update_window(app, 1);
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

	t_frdata fractal;
	fractal.max_iter = MAX_ITER;
	fractal.x = 0.05;
	fractal.y = -0.6805;
	fractal.zoom = 2.0;

	t_app app;
	app.mlx = mlx;
	app.win = win;
	app.img = &img;
	app.fractal = &fractal;
	mlx_mouse_hook(win, mouse_hook, &app);
	mlx_key_hook(win, key_hook, &app);
	// mlx_loop_hook();
	// mlx_hook();
	mlx_set_font(mlx, win, "-bitstream-courier 10 pitch-bold-r-normal--0-0-120-120-m-0-iso8859-1");

	update_window(&app, 1);

	mlx_loop(mlx);

	return (0);
}
