#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <libft.h>
#include <mlx.h>

#include <mlx_utils.h>
#include <keycodes.h>
#include <params.h>

t_color	get_julia_pixel(t_frdata *f, double re, double im)
{
	int iter = 0;
	double re_prev = re;

	while (iter < f->max_iter)
	{
		if (re * re + im * im > 4.0)
			return (t_color) (0xFF * (f->max_iter - iter) / f->max_iter);
		re_prev = re;
		re = re * re - im * im + f->c_re;
		im = 2.0 * re_prev * im + f->c_im;
		iter++;
	}
	return 0x000000;
}

t_color	get_mandelbrot_pixel(t_frdata *f, double c_re, double c_im)
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
	}
	return 0x000000;
}

//  0  1 2 3 4
// -2 -1 0 1 2

//  0  1 2 3 4 5
// -2 -1 0 1 2

void	draw_fractal(t_imgdata *im, t_frdata *fr)
{
	int hw = im->width / 2;
	int hh = im->height / 2;

	for (int y = 0; y < im->height; ++y)
	{
		for (int x = 0; x < im->width; ++x)
		{
			double lx = (double) (x - hw) * fr->zoom * ASPECT / im->width - fr->x;
			double ly = (double) (y - hh) * fr->zoom / im->height - fr->y;
			t_color color = 0xFFFFFF;
			color = get_mandelbrot_pixel(fr, lx, ly);
			// color = get_julia_pixel(fr, lx, ly);
			img_put_pixel(im, x, im->height - y - 1, color);
		}
	}
}

void	update_window(t_app *app)
{
	// puts("called update_window()");

	// mlx_clear_window(app->mlx, app->win);
	draw_fractal(app->img, app->fractal);
	mlx_put_image_to_window(app->mlx, app->win, app->img->img_ptr, 0, 0);
	// mlx_string_put(app->mlx, app->win, 50, 50, 0xEEEEEE, "fract-ol");
	// mlx_string_put(app->mlx, app->win, 50, 80, 0xEEEEEE, "max_iter:");
	// char *zoom_str = ft_itoa(app->fractal->max_iter);
	// if (zoom_str)
	// {
	// 	mlx_string_put(app->mlx, app->win, 200, 80, 0xEEEEEE, zoom_str);
	// 	free(zoom_str);
	// }
}

void	zoom_in(int x, int y, t_app *app)
{
	int w;
	int h;
	double x_rel;
	double y_rel;

	w =  app->img->width;
	h =  app->img->height;

	x_rel = ((double) - w / 2 + x) * ASPECT / w;
	y_rel = ((double) h / 2 - y) / h;

	app->fractal->zoom *= 0.5;
	app->fractal->x -= x_rel * app->fractal->zoom;
	app->fractal->y -= y_rel * app->fractal->zoom;
	update_window(app);
}

void	zoom_out(int x, int y, t_app *app)
{
	int w;
	int h;
	double x_rel;
	double y_rel;

	w =  app->img->width;
	h =  app->img->height;

	x_rel = ((double) - w / 2 + x) * ASPECT / w;
	y_rel = ((double) h / 2 - y) / h;

	app->fractal->x += x_rel * app->fractal->zoom;
	app->fractal->y += y_rel * app->fractal->zoom;
	app->fractal->zoom *= 2.0;
	update_window(app);
}

int	mouse_hook(int keycode, int x, int y, t_app *app)
{
	printf("Mouse keycode %d, x: %d, y: %d\n", keycode, x, y);

	if (keycode == WHEEL_UP)
		zoom_in(x, y, app);
	else if (keycode == WHEEL_DOWN)
		zoom_out(x, y, app);
	// else if (keycode == LEFT_CLICK)

	return (0);
}

void	set_default_fractal(t_frdata *f)
{
	f->zoom = 4.0;
	f->x = 0.0;
	f->y = 0.0;
	f->max_iter = MAX_ITER;

	f->c_re = 0.4;
	f->c_im = 0.15;
}

void	change_max_iter(t_frdata *f, int direction)
{
	int delta;

	delta = direction * ITER_CHANGE_STEP;
	if (f->max_iter + delta <= 0)
	{
		printf("max_iter can't be zero or less!\n");
		return ;
	}
	f->max_iter += delta;
	printf("max_iter: %d\n", f->max_iter);
}

int	key_hook(int keycode, t_app *app)
{
	printf("Keyboard keycode: %d\n", keycode);
	if (keycode == ESC)
		exit(0);
	if (keycode == R)
		set_default_fractal(app->fractal);
	// TODO add bounds
	else if (keycode == COMMA)
		change_max_iter(app->fractal, -1);
	else if (keycode == DOT)
		change_max_iter(app->fractal, 1);
	update_window(app);
	return (0);
}

int	main(int argc, char *argv[])
{
	void		*mlx;
	void		*win;
	t_imgdata	img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, W, H, "fract-ol");
	img.img_ptr = mlx_new_image(mlx, VIEW_W, VIEW_H);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.width = VIEW_W;
	img.height = VIEW_H;

	t_frdata fractal;
	set_default_fractal(&fractal);

	t_app app;
	app.mlx = mlx;
	app.win = win;
	app.img = &img;
	app.fractal = &fractal;
	mlx_mouse_hook(win, mouse_hook, &app);
	mlx_key_hook(win, key_hook, &app);

	mlx_set_font(mlx, win, "-bitstream-courier 10 pitch-bold-r-normal--0-0-120-120-m-0-iso8859-1");

	update_window(&app);

	mlx_loop(mlx);

	return (0);
}
