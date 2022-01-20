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

// For some reason mlx_destroy_display() leads to sigsegv in _XReadEvents()
int	off(void)
{
	printf("Closing application\n");
	exit(0);
	return (0);
}

int	init_app(t_app *a)
{
	a->img->img_ptr = mlx_new_image(a->mlx, VIEW_W, VIEW_H);
	a->img->addr = mlx_get_data_addr(a->img->img_ptr, &a->img->bpp, \
		&a->img->line_len, &a->img->endian);
	a->img->width = VIEW_W;
	a->img->height = VIEW_H;
	a->fractal->color_type = 0;
	set_default_params(a->fractal);
	mlx_mouse_hook(a->win, mouse_hook, a);
	mlx_key_hook(a->win, key_hook, a);
	mlx_hook(a->win, 17, (1L << 2), off, a);
	update_window(a);
	return (1);
}

int	parse_arguments(int argc, char *argv[], t_frdata *fr)
{
	if (argc == 1)
		return (0);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		fr->fr_type = MANDEL;
	else if (ft_strcmp(argv[1], "julia") == 0)
		fr->fr_type = JULIA;
	else if (ft_strcmp(argv[1], "ship") == 0)
		fr->fr_type = SHIP;
	else
		return (0);
	if (argc == 4 && fr->fr_type == JULIA)
	{
		if (!is_valid_float(argv[2]) || !is_valid_float(argv[3]))
			return (0);
		fr->c_re = parse_float(argv[2]);
		fr->c_im = parse_float(argv[3]);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	void		*mlx;
	void		*win;
	t_imgdata	img;
	t_frdata	fractal;
	t_app		app;

	if (!parse_arguments(argc, argv, &fractal))
	{
		printf(HELP_MESSAGE);
		exit(-1);
	}
	mlx = mlx_init();
	win = mlx_new_window(mlx, W, H, "fract-ol");
	app.img = &img;
	app.fractal = &fractal;
	app.mlx = mlx;
	app.win = win;
	if (init_app(&app))
		mlx_loop(mlx);
	return (0);
}
