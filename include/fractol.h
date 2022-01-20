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

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdio.h>

# include <libft.h>
# include <mlx.h>

# include <types.h>
# include <params.h>
# include <keycodes.h>

void	square_plus_c(double *re, double *im, double c_re, double c_im);
int		is_valid_float(char *s);
double	parse_float(char *s);

t_color	rgb_to_int(double r, double g, double b);
void	img_put_pixel(t_imgdata *data, int x, int y, unsigned int color);
t_pfunc	get_pixel_func(t_frdata *fr);
void	draw_fractal(t_imgdata *im, t_frdata *fr);
void	update_window(t_app *app);

t_color	get_mandelbrot_pixel_plain(t_frdata *fr, double c_re, double c_im);
t_color	get_mandelbrot_pixel_modulo(t_frdata *fr, double c_re, double c_im);
t_color	get_mandelbrot_pixel_smooth(t_frdata *fr, double c_re, double c_im);
t_color	get_julia_pixel_plain(t_frdata *fr, double re, double im);
t_color	get_julia_pixel_orbit(t_frdata *fr, double re, double im);
t_color	get_julia_pixel_smooth(t_frdata *fr, double re, double im);
t_color	get_ship_pixel_plain(t_frdata *fr, double c_re, double c_im);
t_color	get_ship_pixel_modulo(t_frdata *fr, double c_re, double c_im);
t_color	get_ship_pixel_smooth(t_frdata *fr, double c_re, double c_im);

void	set_default_params(t_frdata *fr);
void	change_max_iter(t_frdata *fr, int direction);
void	change_color(t_frdata *fr);
void	move_view(t_frdata *fr, int dx, int dy);
int		key_hook(int keycode, t_app *app);

void	zoom_in(int x, int y, t_app *app);
void	zoom_out(int x, int y, t_app *app);
void	set_fractal_constant(int x, int y, t_app *app);
int		mouse_hook(int keycode, int x, int y, t_app *app);

#endif
