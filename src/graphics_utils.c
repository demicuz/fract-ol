/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/01/01 20:20:20 by psharen           #+#    #+#             */
/*   Updated: 2000/01/01 20:20:20 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

// Hardcoded 32 bits per pixel, little-endian
t_color	rgb_to_int(double r, double g, double b)
{
	unsigned int	color;

	color = 0;
	color += r;
	color <<= 8;
	color += g;
	color <<= 8;
	color += b;
	return (color);
}

// Hardcoded 32 bits per pixel, little-endian
// To use arbitrary bpp:
// char *dst;
// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// *(unsigned int*)dst = color;
void	img_put_pixel(t_imgdata *data, int x, int y, unsigned int color)
{
	t_color	*dst;

	dst = (t_color *)data->addr + (y * data->width + x);
	*dst = color;
}

t_pfunc	get_pixel_func(t_frdata *fr)
{
	if (fr->fr_type == MANDEL && fr->color_type == 0)
		return (get_mandelbrot_pixel_plain);
	else if (fr->fr_type == JULIA && fr->color_type == 0)
		return (get_julia_pixel_plain);
	else if (fr->fr_type == SHIP && fr->color_type == 0)
		return (get_ship_pixel_plain);
	else if (fr->fr_type == MANDEL && fr->color_type == 1)
		return (get_mandelbrot_pixel_modulo);
	else if (fr->fr_type == JULIA && fr->color_type == 1)
		return (get_julia_pixel_orbit);
	else if (fr->fr_type == SHIP && fr->color_type == 1)
		return (get_ship_pixel_modulo);
	else if (fr->fr_type == MANDEL && fr->color_type == 2)
		return (get_mandelbrot_pixel_smooth);
	else if (fr->fr_type == JULIA && fr->color_type == 2)
		return (get_julia_pixel_smooth);
	else if (fr->fr_type == SHIP && fr->color_type == 2)
		return (get_ship_pixel_smooth);
	else
		return (get_mandelbrot_pixel_plain);
}

// Hello off-by-one error, my old friend
//  0  1 2 3 4
// -2 -1 0 1 2
//
//  0  1 2 3 4 5
// -2 -1 0 1 2
void	draw_fractal(t_imgdata *im, t_frdata *fr)
{
	int		x;
	int		y;
	double	lx;
	double	ly;
	t_pfunc	func;

	func = get_pixel_func(fr);
	x = 0;
	y = 0;
	while (y < im->height)
	{
		while (x < im->width)
		{
			lx = (x - (double) im->width / 2) * fr->zoom * ASPECT / im->width \
			- fr->x;
			ly = (y - (double) im->height / 2) * fr->zoom / im->height - fr->y;
			img_put_pixel(im, x, im->height - y - 1, func(fr, lx, ly));
			x++;
		}
		x = 0;
		y++;
	}
}

// Can also call mlx_clear_window(app->mlx, app->win), but it's not needed
void	update_window(t_app *app)
{
	draw_fractal(app->img, app->fractal);
	mlx_put_image_to_window(app->mlx, app->win, app->img->img_ptr, 0, 0);
}
