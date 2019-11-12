/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:47:19 by maboye            #+#    #+#             */
/*   Updated: 2019/11/05 19:09:09 by bebosson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
void			fdf_draw_one(t_wolf *data, t_point *p1, t_point *p2, double coef)
{
	t_point	*buf;

	if (p1->x > p2->x)
	{
		buf = p2;
		p2 = p1;
		p1 = buf;
	}
	while (p1->x + data->j <= p2->x)
	{
		data->x1 = p1->x + data->j;
		data->y1 = (int)(p1->y + data->i * coef);
		SDL_RenderDrawPoint(data->renderer, p1->x, p1->y);
		++data->j;

	}
}



void			fdf_draw_sec(t_wolf *data, t_point *p1, t_point *p2, double coef)
{
	t_point	*buf;

	coef = 1 / coef;
	if (p1->y > p2->y)
	{
		buf = p2;
		p2 = p1;
		p1 = buf;
	}
	while (p1->y + data->j <= p2->y)
	{
		data->x1 = (int)(p1->x + data->i * coef);
		data->y1 = p1->y + data->j;
		SDL_RenderDrawPoint(data->renderer, p1->x, p1->y);
		++data->j;
	}
}


static	void	draw_line_bre(t_wolf *data, t_point *p1, t_point *p2)
{
	double	coef;

	data->j = 0;
	if (p2->x == p1->x)
		coef = 1000000;
	else
		coef = (double)(p2->y - p1->y) / (double)(p2->x - p1->x);
	if (coef > -1 && coef < 1)
		fdf_draw_one(data, p1, p2, coef);
	else
		fdf_draw_sec(data, p1, p2, coef);
}
*/


static void			draw_player_minimap(t_wolf *data, int x, int y)
{
	t_point		point[3];
	t_point		player;
	int			dx;
	int 		dy;
	int			i;
	int			j;
	int tmp;
	int			coef;


	data->raydata.eyex = cosf(data->raydata.angle - 5 * 3.14/6);
	data->raydata.eyey = sinf(data->raydata.angle - 5 * 3.14/6);
	point[0].x =  10 * (data->raydata.eyex) + x; //* (data->player.x);
	point[0].y =  10 * (data->raydata.eyey) + y; 
	point[1].x =   10 * cosf(data->raydata.angle + 5 * 3.14/6) + x; 
	point[1].y =   10 * sinf(data->raydata.angle + 5 * 3.14/6) + y;
   	dx = point[1].x - point[0].x;
	dy = point[1].y - point[0].y;
	
	SDL_SetRenderDrawColor(data->renderer, 0, 255, 0, 100);
	SDL_RenderDrawLine(data->renderer, x, y, point[0].x, point[0].y);
	SDL_RenderDrawLine(data->renderer, x, y, point[1].x, point[1].y);
	SDL_RenderDrawLine(data->renderer, point[0].x, point[0].y, point[1].x, point[1].y);
}	

//static void		draw_tra
static void		calc_player(t_wolf *data, int sc_x)
{
	int i;
	SDL_Point pl;


	pl.x =  data->player.x * W_WIDTH / (sc_x * data->map.width);
	pl.y =  data->player.y * W_HEIGHT / (sc_x * data->map.height);
	SDL_SetRenderDrawColor(data->renderer, 0, 0xFF, 0, 0);
	i = -1;
	while (++i < W_WIDTH)
	{
		data->raydata.angle = (data->player.angle - data->player.fov / 2)
			+ ((float)i / (float)W_WIDTH) * data->player.fov;
		SDL_SetRenderDrawColor(data->renderer, 155, 0, 150, 100);
		if (i ==  W_WIDTH / 2)
			draw_player_minimap(data, pl.x, pl.y);
		SDL_RenderDrawLine(data->renderer, pl.x, pl.y, data->map.depth_buffer[i] * W_WIDTH / (sc_x * data->map.width) * (cosf(data->raydata.angle)) + pl.x, data->map.depth_buffer[i] * W_HEIGHT / (sc_x * data->map.height) * (sinf(data->raydata.angle)) + pl.y);
	}
	data->raydata.angle = (data->player.angle - data->player.fov / 2)
			+ ((float)i / (2 * (float)W_WIDTH)) * data->player.fov;
	SDL_SetRenderDrawColor(data->renderer, 155, 150, 150, 100);
	SDL_RenderDrawLine(data->renderer, pl.x, pl.y, data->map.depth_buffer[i / 2] * W_WIDTH / (sc_x * data->map.width) * (cosf(data->raydata.angle)) + pl.x, data->map.depth_buffer[i / 2] * W_HEIGHT / (sc_x * data->map.height) * (sinf(data->raydata.angle)) + pl.y);
}

static void		draw_ray_minimap(t_wolf *data, int nx, int sc_x)
{
	int ny;
	int py;

	ny = -1;
	while (++ny < data->map.height)
	{
		if ((ny + 1) * data->map.width + nx == data->player.pos)
			calc_player(data, sc_x);
	}
}

static void     draw_minimap(t_wolf *data, int nx, int sc_x)
{
	int ny;
 	SDL_Rect rect; 

	ny = -1;
	rect.h = 2 * W_HEIGHT / (sc_x * data->map.height);
	rect.w = 2 * W_WIDTH / (sc_x * data->map.width);
	while (++ny < data->map.height)
	{
		rect.x = nx * W_WIDTH / (sc_x * data->map.width);
		rect.y = ny * W_HEIGHT / (sc_x * data->map.height);
		if (data->map.map[ny * data->map.width + nx] == 1)
			SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 100);
		else
			SDL_SetRenderDrawColor(data->renderer, 155, 0, 0, 100);
			
		SDL_RenderFillRect(data->renderer, &rect);
	}
}

void            minimap(t_wolf *data)
{
	int         nx;
	int			sc_x;

	data->player.pos = (int)data->player.x
		+ ((int)data->player.y + 1) * data->map.width;
	nx = -1;
	//pouvoir le manipuler 
	sc_x = 2;
	while (++nx < data->map.width)
		draw_minimap(data, nx, sc_x) ;
	nx = -1;
	
	while (++nx < data->map.width)
		draw_ray_minimap(data, nx, sc_x);
}
