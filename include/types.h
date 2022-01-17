#ifndef TYPES_H
# define TYPES_H

typedef struct s_imgdata
{
	void	*img_ptr;  // *t_img
	char	*addr; // t_img->data
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int	width;
	int	height;
}	t_imgdata;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_imgdata	*img;
}	t_vars;

typedef struct	s_frdata
{
	double x;
	double y;
	double zoom;
	int max_iter;
}	t_frdata;

typedef struct	s_app
{
	void		*mlx;
	void		*win;
	t_imgdata	*img;
	t_frdata	*fractal;
}	t_app;

typedef unsigned int t_color;

#endif 