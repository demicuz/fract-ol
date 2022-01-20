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

#ifndef TYPES_H
# define TYPES_H

typedef struct s_imgdata
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_imgdata;

typedef struct s_frdata
{
	double	x;
	double	y;
	double	zoom;
	int		max_iter;
	int		fr_type;
	int		color_type;
	double	c_re;
	double	c_im;
}	t_frdata;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	t_imgdata	*img;
	t_frdata	*fractal;
}	t_app;

typedef unsigned int	t_color;
typedef t_color			(*t_pfunc)(t_frdata *fr, double re, double im);

#endif 