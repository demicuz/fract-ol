#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_imgdata
{
	void	*img_ptr;  // *t_img
	char	*addr; // t_img->data
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_imgdata;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_imgdata	*img;
}	t_vars;

typedef struct	s_fractal
{
	long double x;
	long double y;
	long double zoom;
	int max_iter;
}	t_fractal;

typedef struct	s_app
{
	void		*mlx;
	void		*win;
	t_imgdata	*img;
	t_fractal	*fract;
}	t_app;

#endif 