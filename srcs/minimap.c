/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:47:19 by maboye            #+#    #+#             */
/*   Updated: 2019/11/05 02:44:50 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		calc_player(t_wolf *data, int x, int y)
{
	int i;
	int f_x;
	SDL_Point player;
	SDL_Point point[W_WIDTH];
	SDL_Point point2;

	i = -1;
	
	f_x = 4;
//	printf("width map = %d\n",W_WIDTH/data->map.width);
	player.x =  data->player.x * W_WIDTH / (f_x * data->map.width);
	player.y =  data->player.y * W_HEIGHT / (f_x * data->map.height);
	
	
	SDL_SetRenderDrawColor(data->renderer, 0, 0xFF, 0, 0);
	SDL_RenderDrawPoint(data->renderer, x, y);
	while (++i < W_WIDTH)
	{
		data->raydata.angle = (data->player.angle - data->player.fov / 2)
			+ ((float)i / (float)W_WIDTH) * data->player.fov;
		data->raydata.eyex = cosf(data->raydata.angle);
		data->raydata.eyey = sinf(data->raydata.angle);
		point[i].x =  data->map.depth_buffer[i] * W_WIDTH / (f_x * data->map.width) * (data->raydata.eyex) + player.x; //* (data->player.x);
		point[i].y =  data->map.depth_buffer[i] * W_HEIGHT / (f_x * data->map.height) * (data->raydata.eyey) + player.y;// * (data->player.y);
		printf("%d\n",point[i].x);
		printf("%d\n",point[i].y);
		printf("%d\n",W_HEIGHT / (f_x * data->map.height));
	}
	i = -1;

	while (++i < W_WIDTH)
	{
		SDL_SetRenderDrawColor(data->renderer, 55, 0, 0, 100);
		SDL_RenderDrawLine(data->renderer, player.x, player.y, point[i].x, point[i].y);
	}

}

static void		draw_player(t_wolf *data, int nx, int px)
{
	int ny;
	int py;
	int x;

	ny = -1;
	x = 4;
	while (++ny < data->map.height)
	{
		if ((ny + 1) * data->map.width + nx == data->player.pos)
			calc_player(data, nx, ny);
	}
}

static void		info_map(t_wolf *data)
{
	printf("height %d\nwidth%d\nW_WINDOW%d\n",data->map.height,data->map.width,W_WIDTH);


}

static void     draw_minimap(t_wolf *data, SDL_Rect rect, int nx, int px)
{
	int x;
	int ny;
	int py;

	py = 0;
	ny = -1;
//	info_map(data);
	x = 4;
	while (++ny < data->map.height)
	{
		if (data->map.map[ny * data->map.width + nx] == 1)
		{
			SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 100);
			// Set des points SDL
			// les relier aux joueurs lorsque il sont dans alpha 
		}
//		else if ((ny) * data->map.width + nx == data->player.pos)
	//	{
//			//SDL_SetRenderDrawColor(data->renderer, 255, 0, 100, 100);
//			//SDL_RenderDrawPoint(data->renderer, nx + px, ny + py);
//		}			
		else
			SDL_SetRenderDrawColor(data->renderer, 155, 0, 0, 0);
		rect.x = nx * W_WIDTH / (x * data->map.width);
		rect.y = ny * W_HEIGHT / (x * data->map.height);
		rect.h = W_HEIGHT / (x * data->map.height);
		rect.w = W_WIDTH / (x * data->map.width)  ;
;
		SDL_RenderFillRect(data->renderer, &rect);
	}
//	printf("ny = %d",ny);
//	
//	printf("nx = %d",nx);
	//try draw_angle
}

void            minimap(t_wolf *data)
{
	int         nx;
	int         px;
	SDL_Rect    rect;
	int 		x;

	data->player.pos = (int)data->player.x
		+ ((int)data->player.y + 1) * data->map.width;
	
	nx = -1;
	px = 0;
	x = 4;
	

	while (++nx < data->map.width)
		draw_minimap(data, rect, nx, px);
	nx = -1;
	px = 0;

	while (++nx < data->map.width)
		draw_player(data, nx, px);

}
