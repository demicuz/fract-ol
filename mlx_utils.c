#include <mlx_utils.h>

void	img_put_pixel(t_imgdata *data, int x, int y, unsigned int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
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
