#ifndef MLX_UTILS_H
# define MLX_UTILS_H

#include <structs.h>

void			img_put_pixel(t_imgdata *data, int x, int y, unsigned int color);
unsigned int	rgb_to_int(unsigned char r, unsigned char g, unsigned char b);

#endif