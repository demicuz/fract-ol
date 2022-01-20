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

t_color	get_julia_pixel_plain(t_frdata *fr, double re, double im)
{
	int	iter;

	iter = 0;
	while (iter < fr->max_iter)
	{
		if (re * re + im * im > 4.0)
			return ((t_color)(0xFF * (fr->max_iter - iter) / fr->max_iter));
		square_plus_c(&re, &im, fr->c_re, fr->c_im);
		iter++;
	}
	return (0x000000);
}

t_color	get_julia_pixel_orbit(t_frdata *fr, double re, double im)
{
	int		iter;
	double	f;

	iter = 0;
	f = 1e20;
	while (iter < fr->max_iter)
	{
		if (re * re + im * im > 4.0)
			return (0xFFFFFF);
		square_plus_c(&re, &im, fr->c_re, fr->c_im);
		if (f > re * re + im * im)
			f = re * re + im * im;
		iter++;
	}
	f = 1.0 + log2(f) / 16.0;
	return (rgb_to_int(f * 255, f * f * 255, f * f * f * 255));
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
		return (0xFFFFFF);
	r = (re * re + im * im);
	r = iter - log2(log2(r / 2.0)) + 4.0;
	r /= fr->max_iter;
	return (rgb_to_int(r * 255.0, r * r * 255.0, r * r * r * 255.0));
}
