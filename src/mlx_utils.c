#include <mlx_utils.h>

unsigned int	rgb_to_int(double r, double g, double b)
{
	unsigned int	color;

	color = 0;
	color += r;
	color <<= 8;
	color += g;
	color <<= 8;
	color += b;

	return (color);
}

void	img_put_pixel(t_imgdata *data, int x, int y, unsigned int color)
{
	// TODO hardcoded 32 bits per pixel
	t_color	*dst;
	dst = (t_color *)data->addr + (y * data->width + x);
	*dst = color;
	// char *dst;

	// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	// *(unsigned int*)dst = color;
}
