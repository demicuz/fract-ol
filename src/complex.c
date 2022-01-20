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

// For some reason can't pass by reference. Here we are with *re * *re madness
void	square_plus_c(double *re, double *im, double c_re, double c_im)
{
	double	re_prev;

	re_prev = *re;
	*re = *re * *re - *im * *im + c_re;
	*im = 2.0 * re_prev * *im + c_im;
}
