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

#ifndef PARAMS_H
# define PARAMS_H

# define W 1400
# define H 900
# define VIEW_W 1400
# define VIEW_H 900
# define ASPECT 1.55555555

# define MAX_ITER 100
# define MAX_ITER_DELTA 100

# define MANDEL 0
# define JULIA 1
# define SHIP 2

# define COLOR_TYPES 3

# define HELP_MESSAGE "\
Usage: ./fract-ol [mandelbrot | julia | ship]\n\
\n\
You can also pass real and imaginary parts of 'c' constant for Julia fractal:\n\
       ./fract-ol julia 0.4 0.35\n\
They have to be floating point numbers between -10.0 and 10.0 (not inclusive)\n\
\n\
Controls:\n\
. (dot) and , (comma) to change zoom\n\
C to change color\n\
R to reset fractal parameters\n\
Arrows to navigate\n"

#endif