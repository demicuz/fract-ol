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

t_color	get_mandelbrot_pixel_plain(t_frdata *fr, double c_re, double c_im)
{
	int		iter;
	double	re;
	double	im;
	double	q;

	iter = 0;
	re = c_re;
	im = c_im;
	while (iter < fr->max_iter)
	{
		if (re * re + im * im > 20.0)
		{
			q = (double) iter / fr->max_iter;
			if (q > 0.5)
				return (rgb_to_int(q * 255.0, 255, q * 255.0));
			else
				return (rgb_to_int(0, q * 255.0, 0));
		}
		square_plus_c(&re, &im, c_re, c_im);
		iter++;
	}
	return (0x000000);
}

t_color	get_mandelbrot_pixel_modulo(t_frdata *fr, double c_re, double c_im)
{
	int		iter;
	double	re;
	double	im;
	double	q;

	iter = 0;
	re = c_re;
	im = c_im;
	while (iter < fr->max_iter && re * re + im * im < 40.0)
	{
		square_plus_c(&re, &im, c_re, c_im);
		iter++;
	}
	iter %= 20;
	if (iter >= 10)
		iter = -iter + 20;
	q = iter / 10.0;
	return (rgb_to_int(q * 0x9C, q * 0x9C, q * 0xFF));
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
		return (0xFFFFFF);
	r = (re * re + im * im);
	r = iter - log2(log2(r / 2.0)) + 4.0;
	r /= fr->max_iter;
	return (rgb_to_int(r * 255.0, r * r * 255.0, r * r * r * 255.0));
}
