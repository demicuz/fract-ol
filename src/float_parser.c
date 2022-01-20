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

// Horrible, horrible code. But gets the thing done.
int	is_valid_float(char *s)
{
	int	max_digits;

	max_digits = 6;
	if (s && *s == '-')
		s++;
	if (!s || !ft_isdigit(*s))
		return (0);
	s++;
	if (*s != '.')
		return (0);
	s++;
	if (!*s)
		return (0);
	while (*s && ft_isdigit(*s) && max_digits)
	{
		s++;
		max_digits--;
	}
	return (*s == '\0');
}

double	parse_float(char *s)
{
	double	r;
	double	power;
	double	sign;

	r = 1.0;
	power = 0.1;
	sign = 1.0;
	if (*s == '-')
	{
		sign = -1.0;
		r *= sign;
		s++;
	}
	r *= *s - '0';
	s += 2;
	while (*s)
	{
		r += (*s - '0') * power * sign;
		power *= 0.1;
		s++;
	}
	return (r);
}
