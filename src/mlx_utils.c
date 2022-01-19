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
	unsigned int	*dst;
	dst = (unsigned int *)data->addr + (y * data->width + x);
	*dst = color;
	// char *dst;

	// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	// *(unsigned int*)dst = color;
}

// TODO remove util function
void	img_fill(t_imgdata *img_data, unsigned int color)
{
	for (int y = 0; y < img_data->height; ++y)
	{
		for (int x = 0; x < img_data->width; ++x)
		{
			img_put_pixel(img_data, x, y, color);
		}
	}
}
