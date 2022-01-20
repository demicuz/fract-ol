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

void	set_default_params(t_frdata *fr)
{
	fr->zoom = 4.0;
	fr->x = 0.0;
	fr->y = 0.0;
	fr->max_iter = MAX_ITER;
	printf("Set default fractal parameters.\n");
}

void	change_max_iter(t_frdata *fr, int direction)
{
	int	delta;

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

void	move_view(t_frdata *fr, int dx, int dy)
{
	fr->x -= dx * fr->zoom * 0.1;
	fr->y -= dy * fr->zoom * 0.1;
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
	else if (keycode == UP)
		move_view(app->fractal, 0, 1);
	else if (keycode == DOWN)
		move_view(app->fractal, 0, -1);
	else if (keycode == LEFT)
		move_view(app->fractal, -1, 0);
	else if (keycode == RIGHT)
		move_view(app->fractal, 1, 0);
	update_window(app);
	return (0);
}
