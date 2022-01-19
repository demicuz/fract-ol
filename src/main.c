#include "mlx_utils.h"
#include <stdio.h>
// #include <unistd.h>
#include <math.h>
#include <libft.h>
#include <mlx.h>

#include <utils.h>
#include <params.h>

// For some reason can't pass by reference. Here we are with *re * *re madness
void	square_plus_c(double *re, double *im, double c_re, double c_im)
{
	double re_prev;

	re_prev = *re;
	*re = *re * *re - *im * *im + c_re;
	*im = 2.0 * re_prev * *im + c_im;
}

t_color	get_julia_pixel_plain(t_frdata *fr, double re, double im)
{
	int iter;

	iter = 0;
	while (iter < fr->max_iter)
	{
		if (re * re + im * im > 4.0)
			return (t_color) (0xFF * (fr->max_iter - iter) / fr->max_iter);
		square_plus_c(&re, &im, fr->c_re, fr->c_im);
		iter++;
	}
	return 0x000000;
}

t_color	get_julia_pixel_orbit(t_frdata *fr, double re, double im)
{
	int iter = 0;
	double	f = 1e20;

	while (iter < fr->max_iter)
	{
		if (re * re + im * im > 4.0)
			return 0xFFFFFF;
		// return (t_color) (0xFF * (fr->max_iter - iter) / fr->max_iter);
		square_plus_c(&re, &im, fr->c_re, fr->c_im);
		if (f > re * re + im * im)
			f = re * re + im * im;
		iter++;
	}
	f = 1.0 + log2(f) / 16.0;
	float r = f;
	float g = f * f;
	float b = f * f * f;
	return rgb_to_int(r * 255, g * 255, b * 255);
}

t_color	get_julia_pixel_smooth(t_frdata *fr, double re, double im)
{
	int		iter;
	double	r;

	iter = 0;
	while (iter < fr->max_iter && re * re + im * im < 40.0)
	{
		square_plus_c(&re, &im, fr->c_re, fr->c_im);
		iter++;
	}
	if (iter > fr->max_iter - 1)
		return 0xFFFFFF;
	r = (re * re + im * im);
	r = iter - log2(log2(r / 2.0)) + 4.0;
	r /= fr->max_iter;
	return (rgb_to_int(r * 255.0, r * r * 255.0, r * r * r * 255.0));
}

t_color	get_mandelbrot_pixel_plain(t_frdata *fr, double c_re, double c_im)
{
	int		iter;
	double	re;
	double	im;

	iter = 0;
	re = c_re;
	im = c_im;
	while (iter < fr->max_iter)
	{
		if (re * re + im * im > 20.0)
		{
			double q = (double) iter / fr->max_iter;
			if (q > 0.5)
				return (rgb_to_int(q * 255.0, 255, q * 255.0));
			else
				return (rgb_to_int(0, q * 255.0, 0));
		}
		square_plus_c(&re, &im, c_re, c_im);
		iter++;
	}
	return 0x000000;
}

t_color	get_mandelbrot_pixel_modulo(t_frdata *fr, double c_re, double c_im)
{
	int		iter = 0;
	double	re = c_re;
	double	im = c_im;

	while (iter < fr->max_iter)
	{
		if (re * re + im * im > 40.0)
			break;
		// return 0xFFFFFF;
		square_plus_c(&re, &im, c_re, c_im);
		iter++;
	}
	iter %= 20;
	if (iter >= 10)
		iter = -iter + 20;
	double q = iter / 10.0;
	return rgb_to_int(q * 0x9C, q * 0x9C, q * 0xFF);
}

t_color	get_mandelbrot_pixel_smooth(t_frdata *fr, double c_re, double c_im)
{
	int		iter;
	double	re;
	double	im;
	double	r;

	iter = 0;
	re = c_re;
	im = c_im;
	while (iter < fr->max_iter && re * re + im * im < 40.0)
	{
		square_plus_c(&re, &im, c_re, c_im);
		iter++;
	}
	if (iter > fr->max_iter - 1)
		return 0xFFFFFF;
	r = (re * re + im * im);
	r = iter - log2(log2(r / 2.0)) + 4.0;
	r /= fr->max_iter;
	return (rgb_to_int(r * 255.0, r * r * 255.0, r * r * r * 255.0));
}

t_color get_ship_pixel(t_frdata *fr, double c_re, double c_im)
{
	int		iter;
	double	re;
	double	im;

	iter = 0;
	re = c_re;
	im = -c_im;
	c_im = -c_im;
	while (iter < fr->max_iter)
	{
		if (re * re + im * im > 20.0)
		{
			double q = (double) iter / fr->max_iter;
			if (q > 0.5)
				return (rgb_to_int(q * 255.0, 255, q * 255.0));
			else
				return (rgb_to_int(0, q * 255.0, 0));
		}
		if (re < 0.0)
			re = -re;
		if (im < 0.0)
			im = -im;
		square_plus_c(&re, &im, c_re, c_im);
		iter++;
	}
	return 0x000000;
}

t_pixel_func	get_pixel_func(t_frdata *fr)
{
	if (fr->fr_type == MANDEL && fr->color_type == 0)
		return (get_mandelbrot_pixel_plain);
	else if (fr->fr_type == JULIA && fr->color_type == 0)
		return (get_julia_pixel_plain);
	else if (fr->fr_type == SHIP && fr->color_type == 0)
		return (get_ship_pixel);
	else if (fr->fr_type == MANDEL && fr->color_type == 1)
		return (get_mandelbrot_pixel_modulo);
	else if (fr->fr_type == JULIA && fr->color_type == 1)
		return (get_julia_pixel_orbit);
	else if (fr->fr_type == MANDEL && fr->color_type == 2)
		return (get_mandelbrot_pixel_smooth);
	else if (fr->fr_type == JULIA && fr->color_type == 2)
		return (get_julia_pixel_smooth);
	else
		return (get_mandelbrot_pixel_plain);
}

//  0  1 2 3 4
// -2 -1 0 1 2

//  0  1 2 3 4 5
// -2 -1 0 1 2

void	draw_fractal(t_imgdata *im, t_frdata *fr)
{
	double 	lx;
	double 	ly;
	t_color	color;
	t_pixel_func func;

	func = get_pixel_func(fr);
	for (int y = 0; y < im->height; ++y)
	{
		for (int x = 0; x < im->width; ++x)
		{
			lx = (x - (double) im->width / 2) * fr->zoom * ASPECT / im->width - fr->x;
			ly = (y - (double) im->height / 2) * fr->zoom / im->height - fr->y;
			// if (ly > 0.0)
			// 	color = 0xFF;
			// else
			// 	color = 0x0;
			color = func(fr, lx, ly);
			img_put_pixel(im, x, im->height - y - 1, color);
			// img_put_pixel(im, x, im->height - y - 1, color);
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

void	set_fractal_constant(int x, int y, t_app *app)
{
	int w;
	int h;

	w =  app->img->width;
	h =  app->img->height;

	app->fractal->c_re = 2.0 * ((double) - w / 2 + x) * ASPECT / w;
	app->fractal->c_im = 2.0 * ((double) h / 2 - y) / h;
	update_window(app);
}

int	mouse_hook(int keycode, int x, int y, t_app *app)
{
	printf("Mouse keycode %d, x: %d, y: %d\n", keycode, x, y);

	if (keycode == WHEEL_UP)
		zoom_in(x, y, app);
	else if (keycode == WHEEL_DOWN)
		zoom_out(x, y, app);
	else if (keycode == LEFT_CLICK)
		set_fractal_constant(x, y, app);
	return (0);
}

void	set_default_params(t_frdata *fr)
{
	fr->zoom = 4.0;
	fr->x = 0.0;
	fr->y = 0.0;
	fr->max_iter = MAX_ITER;

	fr->c_re = 0.4;
	fr->c_im = 0.15;
	printf("Set default fractal parameters.\n");
}

void	change_max_iter(t_frdata *fr, int direction)
{
	int delta;

	delta = direction * MAX_ITER_DELTA;
	if (fr->max_iter + delta <= 0)
	{
		printf("max_iter can't be zero or less!\n");
		return ;
	}
	fr->max_iter += delta;
	printf("max_iter: %d\n", fr->max_iter);
}

void	change_color(t_frdata *fr)
{
	fr->color_type = (fr->color_type + 1) % COLOR_TYPES;
}

int	key_hook(int keycode, t_app *app)
{
	printf("Keyboard keycode: %d\n", keycode);
	if (keycode == ESC)
		exit(0);
	if (keycode == R)
		set_default_params(app->fractal);
	if (keycode == C)
		change_color(app->fractal);
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
	fractal.fr_type = MANDEL;
	fractal.color_type = 0;
	set_default_params(&fractal);

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
