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

void	zoom_in(int x, int y, t_app *app)
{
	int		w;
	int		h;
	double	x_rel;
	double	y_rel;

	w = app->img->width;
	h = app->img->height;
	x_rel = ((double) - w / 2 + x) * ASPECT / w;
	y_rel = ((double) h / 2 - y) / h;
	app->fractal->zoom *= 0.5;
	app->fractal->x -= x_rel * app->fractal->zoom;
	app->fractal->y -= y_rel * app->fractal->zoom;
	update_window(app);
}

void	zoom_out(int x, int y, t_app *app)
{
	int		w;
	int		h;
	double	x_rel;
	double	y_rel;

	w = app->img->width;
	h = app->img->height;
	x_rel = ((double) - w / 2 + x) * ASPECT / w;
	y_rel = ((double) h / 2 - y) / h;
	app->fractal->x += x_rel * app->fractal->zoom;
	app->fractal->y += y_rel * app->fractal->zoom;
	app->fractal->zoom *= 2.0;
	update_window(app);
}

void	set_fractal_constant(int x, int y, t_app *app)
{
	int	w;
	int	h;

	w = app->img->width;
	h = app->img->height;
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
	else if (keycode == LEFT_CLICK && app->fractal->fr_type == JULIA)
		set_fractal_constant(x, y, app);
	return (0);
}
