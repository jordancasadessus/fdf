/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:41:14 by ltressen          #+#    #+#             */
/*   Updated: 2023/05/18 16:31:34 by jcasades         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(char *color)
{
	int	colors;
	int	i;

	colors = 0;
	i = 2;
	while (i < 8)
	{
		if (color[i] >= '0' && color[i] <= '9')
			colors += (ft_power(color[i] - 48, 8 - i));
		else
			colors += (ft_power(color[i] - 49, 8 - i));
		i++;
	}
	return (colors);
}

		


int	parsing_color(t_point one, t_point two, int i, int total)
{
	int	colorone;
	int	colortwo;

	colorone = 16777215;
	colortwo = 16777215;
	if (!one.color && !two.color)
		return (16777215);
	if (two.color)
		colortwo = get_color(two.color);
	if (one.color)
		colorone = get_color(one.color);
	(void)colortwo;
	(void)i;
	(void)total;
	return (colorone);
}
	
void	ft_intsplit(t_pbl *map, char *line)
{
	static int x = 0;
	char	**tmp;
	int	y;
	char	**point;

	y = 0;
	tmp = ft_split(line, ' ');
	while(tmp[y])
		y++;
	map->wth = y;
	map->pix[x] = ft_calloc(y + 1, sizeof(t_point));
	y = 0;
	while (tmp[y])
	{
		point = ft_split(tmp[y], ','); 
		map->pix[x][y].z = ft_atoi(point[0]);
		if (point[1])
		{
			map->pix[x][y].color = point[1];
			map->pix->colorflag = 1;
		}
		if (map->pix[x][y].z > map->zmax)
			map->zmax = map->pix[x][y].z;
		if (map->pix[x][y].z < map->zmin)
			map->zmin = map->pix[x][y].z;
		free(tmp[y]);
		y++;
	}
	free(tmp);
	x++;
}

void	read_file(t_pbl *map, char *name)
{
	int	file;
	char	*line;
	int	i;


	i = 1;
	file = open(name, O_RDONLY);
	line = get_next_line(file);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		i++;
	}
	close(file);
	map->hgt = i - 1;
	map->pix = malloc(sizeof(t_point *) * i);
	file = open(name, O_RDONLY);
	line = get_next_line(file);
	while (line)
	{
		ft_intsplit(map, line);
		free(line);
		line = get_next_line(file);
 	}
	return ;
}
